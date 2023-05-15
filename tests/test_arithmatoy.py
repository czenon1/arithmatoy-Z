import operator
import subprocess
from pathlib import Path
from random import Random

from _pytest.fixtures import FixtureRequest

tests_count_per_base = 10
cli_path = Path(".local/cmake/dist/bin/arithmatoy-cli")


def test_add(
    request: FixtureRequest,
):
    run_tests("add", request)


def test_sub(
    request: FixtureRequest,
):
    run_tests("sub", request)


def test_mul(
    request: FixtureRequest,
):
    run_tests("mul", request)


def run_tests(
    operator_str: str,
    request: FixtureRequest,
):
    Path(f"tests/outputs/test_{operator_str}").mkdir(parents=True, exist_ok=True)
    operator_lambda = getattr(operator, operator_str)
    rng = Random(0)

    for base in range(2, 36):
        for i in range(tests_count_per_base):
            lhs = rng.randint(0, 2**256)
            rhs = rng.randint(2, 2**256)
            if operator_str == "sub" and lhs < rhs:
                lhs, rhs = rhs, lhs
            lhs_str = dec_to_base(lhs, base)
            rhs_str = dec_to_base(rhs, base)
            cp = subprocess.run(
                [
                    cli_path,
                    operator_str,
                    f"{base}",
                    f"{lhs_str}",
                    f"{rhs_str}",
                    "--verbose",
                ],
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                universal_newlines=True,
            )
            result_str = cp.stdout.strip().split(" = ")[1]
            expected_result = operator_lambda(lhs, rhs)
            expected_result_str = dec_to_base(expected_result, base)
            assert result_str == expected_result_str
            str_output = f'{" ".join(cp.args[1:])}\n{cp.stdout}{cp.stderr}'
            if request.config.getoption("force_regen"):
                with open(
                    f"tests/outputs/test_{operator_str}/test_{operator_str}_base{base}_{i:02}.txt",
                    "w",
                    newline="\n",
                ) as io:
                    io.write(str_output)
            else:
                expected_output = Path(
                    f"tests/outputs/test_{operator_str}/test_{operator_str}_base{base}_{i:02}.txt"
                ).read_text()
                assert str_output == expected_output


def dec_to_base(num, base):  # Maximum base - 36
    # https://www.codespeedy.com/inter-convert-decimal-and-any-base-using-python/
    base_num = ""
    while num > 0:
        dig = int(num % base)
        if dig < 10:
            base_num += str(dig)
        else:
            base_num += chr(ord("a") + dig - 10)  # Using uppercase letters
        num //= base
    base_num = base_num[::-1]  # To reverse the string
    return base_num
