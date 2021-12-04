from unittest import TestCase
from utils import *


def scanner():
    return get_int()


def algorithm(target):
    ways = 0

    def helper(target, curr):
        nonlocal ways
        if curr > target:
            return None
        if curr == target:
            ways += 1
            return None
        for i in range(1, 7):
            helper(target, curr + i)

    helper(target, 0)
    return ways


def test_1():
    assert algorithm(3) == 4


def test_2():
    assert algorithm(5) == 16


if __name__ == "__main__":
    print(algorithm(scanner()))
