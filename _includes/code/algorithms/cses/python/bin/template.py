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
    pass

### Algorithm
def algorithm():
    pass

### Output
def printer():
    pass 

### Tests
class Tests(TestCase):
    def test_1(self):
        self.assertEqual(algorithm(), [])
    
    def test_2(self):
        self.assertEqual(algorithm(), [])
    
    def test_3(self):
        self.assertEqual(algorithm(), [])


if __name__ == "__main__":
    # printer(algorithm(scanner()))
    pass
