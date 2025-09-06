---
title: maximum-subarray-sum
---



# Maximum Subarray Sum

Prev: [sum-of-two-values](sum-of-two-values.md)
Next: [stick-lengths](stick-lengths.md)

Given an array of n integers, your task is to find the maximum sum of
values in a contiguous, nonempty subarray.

Input

The first input line has an integer n: the size of the array.

The second line has n integers x1,x2,...,xn: the array values.

Output

Print one integer: the maximum subarray sum.

## Explanation

We want to find the maximum sum of values. We'll start out by taking
the first item in the array and calling that our maximum. Then, for
every value we have two choices: either we take the next item and add it
to our current running total, or we restart with just this item. We have
to update our current and maximum values, and we're done.

## Solution

```cpp
{{# include _include/code/algorithms/cses/cpp/sorting-and-searching/maximum-subarray-sum.cc }}
```

Prev: [sum-of-two-values](sum-of-two-values.md)
Next: [stick-lengths](stick-lengths.md)
