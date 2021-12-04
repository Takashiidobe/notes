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

d1 = [False] * 15
d2 = [False] * 15
c = [False] * 8
ans = 0

### Stdin Scanner
b = [input() for _ in range(8)]

### Algorithm
def algorithm(r):
    global ans
    if r == 8:
        ans += 1
    else:
        for i in range(8):
            if b[r][i] == '*':
                continue
            if c[i] or d1[r + i] or d2[i - r + 7]:
                continue
            c[i] = True
            d1[r + i] = True
            d2[i - r + 7] = True
            algorithm(r + 1)
            c[i] = False 
            d1[r + i] = False 
            d2[i - r + 7] = False 

### Output
def printer(ans):
    print(ans)

### Tests
class Tests(TestCase):
    def test_1(self):
        self.assertEqual(algorithm(), [])

    def test_2(self):
        self.assertEqual(algorithm(), [])

    def test_3(self):
        self.assertEqual(algorithm(), [])


if __name__ == "__main__":
    algorithm(0)
    printer(ans)
