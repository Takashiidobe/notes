import sys


def list_to_str(l):
    return ' '.join([str(i) for i in l])

def get_line():
    line = sys.stdin.readline()
    return line.strip()

def get_int():
    return int(get_line())

def get_spaced_ints():
    line = sys.stdin.readline().strip()
    return list(map(lambda x: int(x), line.split(' ')))
