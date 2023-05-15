import math
from random import Random

import pytest
from tests.tp import *

rng = Random(42)
random_test_count = 1024


def test_nombre_entier():
    assert nombre_entier(0) == "0"
    assert nombre_entier(1) == "S0"
    assert nombre_entier(7) == "SSSSSSS0"
    for _ in range(random_test_count):
        n = rng.randint(0, 2**32)
        x = nombre_entier(n)
        assert x.endswith("0")
        assert x.startswith("S" * n)
        assert len(x) == n + 1


def test_successeur():
    assert S("0") == "S0"
    assert S("S0") == "SS0"
    assert S("SSSSSSS0") == "SSSSSSSS0"
    for _ in range(random_test_count):
        n = rng.randint(0, 2**32)
        x = nombre_entier(n)
        assert S(x) == "S" + x


def test_addition():
    assert addition("SS0", "SSS0") == "SSSSS0"
    assert addition("0", "SS0") == "SS0"
    assert addition("SS0", "0") == "SS0"
    for _ in range(random_test_count):
        a = rng.randint(0, 2**32)
        b = rng.randint(0, 2**32)
        result = a + b
        assert nombre_entier(result) == addition(a, b)


def test_multiplication():
    assert multiplication("SS0", "SSS0") == "SSSSSS0"
    assert multiplication("0", "SS0") == "0"
    assert multiplication("SS0", "0") == "0"
    for _ in range(random_test_count):
        a = rng.randint(0, 2**32)
        b = rng.randint(0, 2**32)
        result = a * b
        assert nombre_entier(result) == multiplication(a, b)


def test_facto_ite():
    assert facto_ite(0) == 1
    assert facto_ite(7) == 5040
    for _ in range(random_test_count):
        a = rng.randint(0, 2**32)
        assert facto_ite(a) == math.factorial(a)


def test_facto_rec():
    assert facto_rec(0) == 1
    assert facto_rec(7) == 5040
    for _ in range(random_test_count):
        a = rng.randint(0, 2**32)
        assert facto_rec(a) == math.factorial(a)


def test_fibo_rec():
    assert fibo_rec(0) == 0
    assert fibo_rec(1) == 1
    assert fibo_ite(2) == 1
    assert fibo_ite(12) == 144
    for a in range(2, 32):
        assert fibo_ite(a) == fibo_ite(a - 1) + fibo_ite(a - 2)


def test_fibo_ite():
    assert fibo_ite(0) == 0
    assert fibo_ite(1) == 1
    assert fibo_ite(2) == 1
    assert fibo_ite(12) == 144
    for _ in range(random_test_count):
        a = rng.randint(2, 2**8)
        assert fibo_ite(a) == fibo_ite(a - 1) + fibo_ite(a - 2)


def test_golden_phi():
    phi = (1 + math.sqrt(5)) / 2
    prev_delta = math.inf
    for n in range(1, 16):
        delta = abs(golden_phi(n) - phi)
        assert delta < prev_delta
        prev_delta = delta


def test_sqrt5():
    target = math.sqrt(5)
    prev_delta = math.inf
    for n in range(1, 16):
        delta = abs(sqrt5(n) - target)
        assert delta < prev_delta
        prev_delta = delta


def test_pow():
    assert pow(12.4, 12) == pytest.approx(13214788658781.803)
    assert pow(42, 2**16) == pytest.approx(42 ** (2**16))
