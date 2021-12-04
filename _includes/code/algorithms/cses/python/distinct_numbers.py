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
def algorithm(n):
    return len(set(n)) 

### Output
def printer(f):
    print(f) 

### Tests
class Tests(TestCase):
    def test_1(self):
        self.assertEqual(algorithm([]), 0)
    
    def test_2(self):
        self.assertEqual(algorithm([2,2]), 1)
    
    def test_3(self):
        self.assertEqual(algorithm([1,2,3,3]), 3)


if __name__ == "__main__":
    printer(algorithm(scanner()))
