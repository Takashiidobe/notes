#!/usr/bin/env python

from random import shuffle

with open('random_words.txt') as infile, open('million_lines.txt', 'w+') as outfile:
    lines = [line for line in infile]
    for _ in range(20000):
        shuffle(lines)
        outfile.writelines(lines)
