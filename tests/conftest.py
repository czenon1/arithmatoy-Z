from typing import Any


def pytest_addoption(parser: Any) -> None:
    parser.addoption(
        "--force-regen",
        action="store_true",
        default=False,
        help="Force regen regression data files",
    )
