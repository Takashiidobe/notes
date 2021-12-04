from unittest import TestCase
from utils import *


def scanner():
    return get_line()


def algorithm(s):
    if len(s) == 0 || len(s) == 1:
        return 0
    s_shifted = s[1:]
    zipped = zip(s, s_shifted)
    curr = 1
    max_so_far = 1
    for l, r in zipped:
        max_so_far = max(max_so_far, curr)
        if l == r:
            curr += 1
        else:
            curr = 1

    return max_so_far


def test_1():
    assert algorithm('ATTCGGGA') == 3


def test_2():
    assert algorithm('') == 0


def test_3():
    assert algorithm('AT') == 1


def test_4():
    assert algorithm('T') == 1


if __name__ == "__main__":
    print(algorithm(''))
    print(algorithm(scanner()))
