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
    return get_int()

### Algorithm
A = [3,2,1]
B = []
C = []

def algorithm(n, left, mid, right, ans = []):
    """
    1 -> 1
    [1] [] [0]
    [] [] [1]
    """
    """
    2 -> 3
    [2] [1] []
    [] [1] [2]
    [] [] [2,1]
    """
    """
    3 -> 7 
    [3, 2] [] [1]
    [3] [2] [1]
    [3] [2,1] []
    [3] [2,1] [3]
    [1] [2] [3]
    [1] [] [3, 2]
    [] [] [3, 2, 1]
    """
    if n > 0:
        # Move n - 1 disks from source to auxiliary, so they are out of the way
        algorithm(n - 1, source, aux, target)

        popped = source.pop()
        # Move the nth disk from source to target
        target.append(source.pop())

        # Display our progress
        print(A, B, C, '##############', sep='\n')

        # Move the n - 1 disks that we left on auxiliary onto target
        algorithm(n - 1, aux, target, source)


        


### Output
def printer(l):
    print(len(l))
    for l, r in l:
        print(f"{l} {r}")

### Tests
class Tests(TestCase):
    def test_1(self):
        self.assertEqual(algorithm(), [])
    
    def test_2(self):
        self.assertEqual(algorithm(), [])
    
    def test_3(self):
        self.assertEqual(algorithm(), [])



if __name__ == "__main__":
    algorithm(3, A, C, B)
