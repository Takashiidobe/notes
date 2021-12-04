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

def to_sorted_unique_list(inp):
    return list(sorted(set(inp)))

### Stdin Scanner
def scanner():
    return get_line()

### Algorithm
def algorithm(seq):
    if len(seq) <= 1:
        yield seq
    else:
        for item in algorithm(seq[1:]):
            for i in range(len(seq)):
                yield item[:i] + seq[0] + item[i:]
### Output
def printer(inp):
    ans = to_sorted_unique_list(inp)
    print(len(ans))
    print(*ans, sep='\n')

### Tests
class Tests(TestCase):
    def test_1(self):
        ans = to_sorted_unique_list({'cbaaa', 'caaab', 'aaabc', 'bacaa', 'aabca', 'abcaa', 'aacab', 'acaba', 'aacba', 'acaab', 'aabac', 'aaacb', 'abaac', 'bcaaa', 'acbaa', 'baaca', 'abaca', 'cabaa', 'caaba', 'baaac'})
        self.assertEqual(to_sorted_unique_list(algorithm('aabac')), ans)
    
    def test_2(self):
        self.assertEqual(algorithm(0), [])
    
    def test_3(self):
        self.assertEqual(algorithm(0), [])


if __name__ == "__main__":
    printer(algorithm(scanner()))
