---
title: ferris-wheel
---

# Ferris Wheel

Prev: [apartments](apartments.md)
Next: [concert-tickets](concert-tickets.md)

There are n children who want to go to a Ferris wheel, and your task is
to find a gondola for each child.

Each gondola may have one or two children in it, and in addition, the
total weight in a gondola may not exceed x. You know the weight of every
child.

What is the minimum number of gondolas needed for the children?

Input

The first input line contains two integers n and x: the number of
children and the maximum allowed weight.

The next line contains n integers p1,p2,...,pn: the weight of each
child.

Output

Print one integer: the minimum number of gondolas.

## Explanation

Since each gondola can have one or two children in it, we can go greedy.

Let's put the children into a sorted collection, and iterate through
from smallest to largest.

We want to find the largest number where the maximum allowed weight -
current child >= 0.

If we can find that, increment the answer, and remove both from the
collection.

If we can't find it (the index is out of bounds), then we'll just
remove our current child and move on.

## Solution

```cpp
{{# include _include/code/algorithms/cses/cpp/sorting-and-searching/ferris-wheel.cc }}
```

Prev: [apartments](apartments.md)
Next: [concert-tickets](concert-tickets.md)
