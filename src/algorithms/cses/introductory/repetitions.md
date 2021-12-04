---
title: repetitions
---

# Repetitions

Prev: \[missing-number](missing-number.md) Next:
\[increasing-array](increasing-array.md)

You are given a DNA sequence: a string consisting of characters A, C, G,
and T. Your task is to find the longest repetition in the sequence. This
is a maximum-length substring containing only one type of character.

Input

The only input line contains a string of n characters.

Output

Print one integer: the length of the longest repetition.

## Approach

Iterate through the buffer with two pointers, counting where the left
and right pointers are the same. Hold that in a maximum variable, and
continue on.

```cpp
{{# include _include/code/algorithms/cses/cpp/introductory/repetitions.cc }}
```

Prev: \[missing-number](missing-number.md) Next:
\[increasing-array](increasing-array.md)
