### Helpers
from unittest import TestCase
from sys import stdin

def list_to_str(l):
    return ' '.join(str(i) for i in l)

def get_line():
    line = stdin.readline()
    return line.strip()

def get_int():
    return int(get_line())

def get_spaced_ints():
    line = stdin.readline().strip()
    return list(map(lambda x: int(x), line.split(' ')))

### Stdin Scanner
def scanner():
    _ = get_int()
    return get_spaced_ints()


### Algorithm
def algorithm(index, a, b):
    if index >= len(inp):
        return abs(a - b)

    return min(algorithm(index + 1, a + inp[index], b), algorithm(index + 1, a, b + inp[index]))

### Output
def printer(r):
    print(r)


### Tests
class Tests(TestCase):
    pass


if __name__ == "__main__":
    inp = scanner()
    r = algorithm(0, 0, 0)
    printer(r)
        


