---
title: sum-of-two-values
---

of Two Values\"

# Sum of Two Values

Prev: \[movie-festival](movie-festival.md) Next:
\[maximum-subarray-sum](maximum-subarray-sum.md)

You are given an array of n integers, and your task is to find two
values (at distinct positions) whose sum is x.

Input

The first input line has two integers n and x: the array size and the
target sum.

The second line has n integers a1,a2,\...,an: the array values.

Output

Print two integers: the positions of the values. If there are several
solutions, you may print any of them. If there are no solutions, print
IMPOSSIBLE.

## Explanation

The classic two sum. Create a map with \[value - curr\] = curr_index and
iterate through the map. If you find curr in the map, you have a match,
print it out.

## Solution

```cpp
{{# include _include/code/algorithms/cses/cpp/sorting-and-searching/distinct-numbers.cc }}
```

Prev: \[movie-festival](movie-festival.md) Next:
\[maximum-subarray-sum](maximum-subarray-sum.md)
