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
    get_int()

### Algorithm
def algorithm(n):
    if n == 3:
        return [] 

### Output
def printer(n):
    if n == []:
        print("NO SOLUTION")
    else:
        print(list_to_str(n))

### Tests
class Tests(TestCase):
    def test_1(self):
        self.assertEqual(algorithm(5), [4,2,5,3,1])
    
    def test_2(self):
        self.assertEqual(algorithm(3), [])
    
    def test_3(self):
        self.assertEqual(algorithm(1), [])


if __name__ == "__main__":
    printer(algorithm(scanner()))
