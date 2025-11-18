---
title: "Pattern Defeating Quicksort"
pdf_url: "[[pattern-defeating-quicksort.pdf]]"
---
## Notes

Pattern defeating quicksort is a hybrid sorting algorithm with the following goals:

1. $log(n)$ memory usage.
2. fast average case
3. deterministically avoids bad worst case behavior
4. Runs in linear time for a few patterns

It is also still unstable.

Pattern defeating quicksort uses insertion sort for small data sets due to its good performance even with $O(n^2)$ complexity.
It then has quicksort as the second sort, and heapsort as the fallback sort.

The quicksort uses a median of three pivot selection scheme, with two additions:

1. defining a "bad partition" and tracking that, and swapping a couple of elements to break bad patterns.
2. handling ascending/descending sequences with little overhead.
