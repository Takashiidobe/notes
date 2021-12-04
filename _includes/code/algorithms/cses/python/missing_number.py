from unittest import TestCase
from utils import *


def scanner():
    return (get_int(), get_spaced_ints())


def algorithm(n, nums):
    return sum([x for x in range(n+1)]) - sum(nums)


def test_1():
    assert algorithm(5, [2, 3, 1, 5]) == 4


if __name__ == "__main__":
    print(algorithm(*scanner()))
