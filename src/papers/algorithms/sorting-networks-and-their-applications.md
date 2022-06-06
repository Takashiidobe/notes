---
title: "Sorting networks and their applications"
---

This paper introduces two ways of executing merge sort in parallel, in a
time complexity of (log N), odd-even merge and Bitonic merge.

## Odd-even merge

Odd even merge sort involves merging two sorted lists into one sorted
list. It does the following:

1. Take A and B, two sorted lists
2. Split the two lists into two parts, with one list carrying the even
   indexes and odd indexes for each sublist.
3. Recursively merge the even indexed lists of both sides, and odd
   indexed lists of both sides, to obtain two sorted lists.
4. Interleave these two lists to get an almost-sorted list.
5. Rearrange neighbors using compare-and-swap operations to completely
   sort the list.

This allows for O (log N) compare-and-swap operations that are
parallelizable.

This is doable in O (log (n)), since there are log(n) sorting steps and
each step takes (log N) time.

## Bitonic merge

Bitonic Mergesort involves taking an unsorted sequence and transforming
it into a bitonic sequence, where the numbers are always increase and
then decreasing, or vice versa.

We can create a bitonic sequence with compare and swap in by trying to
swap the ith and i + (n/2)th numbers which each other in an ordered
fashion.

Take the sequence:

[3, 5, 7, 4]

In parallel, try to swap 3, 7, and 5 and 4:

3 and 7 are not swapped, since they are ordered, but 4 and 5 are
swapped.

Thus, the final array is:

[3, 4, 7, 5], which has two bitonic sequences (the first half and second
half). As well, all values in the left sequence are less than the ones
on the right. We then recursively apply compare-and-swap on smaller
arrays until we get a sorted sequence --

We take [3,4], which is already ordered, nothing to do.

We take [7,5], which isn't ordered. We then swap these, to get the final
sequence, [3,4,5,7].

Let's take a full example, and prove it sorts in 2 (log N) time. (6
steps)

Take this array which has 8 elements.

[8, 3, 2, 5, 1, 4, 6, 7]

First, bitonically sort in pairs, i.e. (0, 1), (2, 3), (4, 5), (6, 7)

(0, 1) should be increasing
(2, 3) should be decreasing
(4, 5) should be increasing
(6, 7) should be decreasing

So:

[8, 3] -> [3, 8]
[2, 5] -> [5, 2]
[1, 4] -> [1, 4]
[6, 7] -> [7, 6]

Next, we sort the range [0..4] and [4..8] by having the first half
increasing and the second half decreasing. We do this by comparing the
ith and (i + n / 2)th items.

For the first half, [3, 8, 5, 2], we compare:

[3, 5] -> [3, 5]
[8, 2] -> [2, 8]

The first half is now [3, 5, 2, 8].

The second half, [7, 6, 1, 4] should be sorted decreasing:

[1, 7] -> [7, 1]
[4, 6] -> [6, 4]

The second half is now [7, 1, 6, 4]

Then swap the adjacent pairs but increasing for [0..4] and decreasing
for [4..8]

[3, 2] -> [2, 3]
[5, 8] -> [5, 8]

The first half is [2, 3, 5, 8]

[7, 6] -> [7, 6]
[1, 4] -> [4, 1]

The second half is [7, 6, 4, 1]

Then sort the halves:

[2, 7] -> [2, 7]
[3, 6] -> [3, 6]
[5, 4] -> [4, 5]
[8, 1] -> [1, 8]

The sequence is now:

[2, 3, 4, 1, 7, 6, 5, 8]

Then we swap increasingly in halves:

[2, 1, 4, 3, 5, 6, 7, 8]

And then swap adjacent members:

[1, 2, 3, 4, 5, 6, 7, 8]

This is all doable in 6 steps, as long as all compare-and-swap
operations are done in parallel, which means we require (n/2) threads to
sort in (log N) time.
