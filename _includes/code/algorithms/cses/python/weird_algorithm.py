### Helpers

from unittest import TestCase
import sys

def list_to_str(l):
    return ' '.join(str(i) for i in l)

def get_line():
    line = sys.stdin.readline()
    return line.strip()

def get_int():
    return int(get_line())

def get_spaced_ints():
    line = sys.stdin.readline().strip()
    return list(map(lambda x: int(x), line.split(' ')))

### Stdin Scanner

def scanner():
    return get_int()

### Algorithm

def algorithm(n, path=[]):
    path = path + [n]
    if n == 1:
        return path
    if n % 2 == 0:
        return algorithm(n // 2, path)
    else:
        return algorithm(3 * n + 1, path)

### Output

def printer(f):
    print(list_to_str(f()))

### Tests

class Tests(TestCase):
    def test_1(self):
        self.assertEqual(algorithm(20), [20,10,5,16,8,4,2,1])
    
    def test_2(self):
        self.assertEqual(algorithm(4), [4,2,1])
    
    def test_3(self):
        self.assertEqual(algorithm(3), [3,10,5,16,8,4,2,1])


if __name__ == "__main__":
    printer(algorithm(scanner()))
