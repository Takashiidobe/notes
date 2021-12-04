---
title: missing-number
---

Number\"

# Missing Number

Prev: \[weird-algorithm](weird-algorithm.md) Next:
\[repetitions](repetitions.md)

You are given all numbers between 1,2,\...,n except one. Your task is to
find the missing number.

Input

The first input line contains an integer n.

The second line contains n−1 numbers. Each number is distinct and
between 1 and n (inclusive).

Output

Print the missing number.

(n \* (n + 1) / 2) is the sum of the first (1..n+1) numbers. subtract
that from the sum total that we have.

```cpp
{{# include _include/code/algorithms/cses/cpp/introductory/missing-number.cc }}
```

Prev: \[weird-algorithm](weird-algorithm.md) Next:
\[repetitions](repetitions.md)
