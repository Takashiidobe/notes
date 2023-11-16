---
title: "Sorting"
---

# Sorting

Prev: [data-structures](data-structures.md)
Next: [divide-and-conquer](divide-and-conquer.md)

## Exercises

4-1. The Grinch is given the job of partitioning $2n$ players into two teams of $n$
players each. Each player has a numerical rating that measures how good he or
she is at the game. The Grinch seeks to divide the players as unfairly as possible,
so as to create the biggest possible talent imbalance between the teams. Show
how the Grinch can do the job in $O(n log n)$ time.

This can be done in $O n(log n)$ by sorting the array of ratings and then splitting the team into [..mid] and [mid+1..]:

```python
def unbalanced_teams(ratings: List[int]) -> (List[int], List[int]):
    sorted_ratings = sorted(ratings)
    mid = len(sorted_ratings) // 2
    return (sorted_ratings[0..mid], sorted_ratings[mid+1..])
```

Otherwise, there is a $O(n)$ algorithm. You can quickselect for the midpoint in $O(n)$ time and then return the two halves of the array.

4-2. For each of the following problems, give an algorithm that finds the desired numbers within the given amount of time. To keep your answers brief, feel free to use algorithms from the book as subroutines. For the example, $S = {6, 13, 19, 3, 8}$, $19 − 3$ maximizes the difference, while $8 − 6$ minimizes the difference.

(a) Let $S$ be an unsorted array of $n$ integers. Give an algorithm that finds the pair $x, y \in S$ that maximizes $|x − y|$. Your algorithm must run in $O(n)$ worst-case time.

Keep track of two numbers, `min` and `max`. Iterate through the array, finding the `minimum` and `maximum` of the array. Then, subtract the pair.

```python
    def maximize_difference(a: List[int]) -> int:
        if not a:
            return 0
        x, y = min(a), max(a)
        return y - x
```

(b) Let $S$ be a sorted array of $n$ integers. Give an algorithm that finds the pair $x, y \in S$ that maximizes $|x − y|$. Your algorithm must run in O(1) worst-case time.

The same, but just take the first and last item of the array and subtract them.
```python
    def maximize_difference_sorted(a: List[int]) -> int:
        if not a:
            return 0
        x, y = a[0], a[-1]
        return y - x
```

(c) Let $S$ be an unsorted array of n integers. Give an algorithm that finds the pair $x, y \in S$ that minimizes $|x − y|$, for $x \ne y$. Your algorithm must run in $O(n log n)$ worst-case time.

Sort the array, then iterate through the pairs of the array. Keep the one with the minimum difference.

```python
    def minimize_difference_unsorted(a: List[int]) -> int:
        if len(a) < 2:
            return 0
        a.sort()
        minimum_distance = float('inf')
        curr_pair = None
        for left, right in zip(a, a[1..]):
            distance = right - left
            if distance < minimum_distance:
                curr_pair = (left, right)
                minimum_distance = distance
        return curr_pair
```

(d) Let $S$ be a sorted array of n integers. Give an algorithm that finds the pair $x, y \in S$ that minimizes $|x − y|$, for $x \ne y$. Your algorithm must run in $O(n)$ worst-case time.

The same algorithm as above, without sorting.

```python
    def minimize_difference_unsorted(a: List[int]) -> int:
        if len(a) < 2:
            return 0
        minimum_distance = float('inf')
        curr_pair = None
        for left, right in zip(a, a[1..]):
            distance = right - left
            if distance < minimum_distance:
                curr_pair = (left, right)
                minimum_distance = distance
        return curr_pair
```


4-3. Take a list of $2n$ real numbers as input. Design an $O(n log n)$ algorithm
that partitions the numbers into n pairs, with the property that the partition
minimizes the maximum sum of a pair. For example, say we are given the
numbers $(1,3,5,9)$. The possible partitions are $((1,3),(5,9))$, $((1,5),(3,9))$, and $((1,9),(3,5))$. The pair sums for these partitions are $(4,14)$, $(6,12)$, and $(10,8)$.Thus, the third partition has 10 as its maximum sum, which is the minimum over the three partitions.

The way the pair sums could be minimized is by sorting the list of $2n$ numbers, and then pairing the first and last numbers of the array. This minimizes the total sum of the entire partition.

### Heaps

4-17. Devise an algorithm for finding the $k$ smallest elements of an unsorted set of n integers in $O(n + k log n)$.

Add all the unsorted items into a min-heap, and pop the first $k$ elements.

4-18. Give an $O(n log k)$-time algorithm that merges k sorted lists with a total of n elements into one sorted list. (Hint: use a heap to speed up the obvious $O(kn)$-time algorithm).

Since the lists are sorted, the naive method takes $O(kn)$ time by taking the minimum item of every list, until we traverse the lists. There is a better algorithm that involves putting all of the items from each list into a heap, and then taking the minimum item from there. Then, we add another element from that list, and then traversing the list. This avoids the overhead of needing to scan each of the $n$ lists $k$ times to find the minimal item, instead taking $log n$ time, dropping the runtime to $O(n log k)$.

4-19. You wish to store a set of n numbers in either a max-heap or a sorted array. For each application below, state which data structure is better, or if it does not matter. Explain your answers.

(a) Find the maximum element quickly.

If the sorted array does not need to support insertions and maintain the invariant that it is sorted, they are both the same. However, a heap is better if there are insertions, deletions, or updates.

(b) Delete an element quickly.

If the sorted array needs to maintain being sorted, then the heap is better, otherwise they are both the same.

(c) Form the structure quickly.

Arrays are faster to create, since heapify takes an additional $O(n)$ time to create.

(d) Find the minimum element quickly.

If the sorted array does not need to support insertions and maintain the invariant that it is sorted, they are both the same. However, a heap is better if there are insertions, deletions, or updates.

4-20.
(a) Give an efficient algorithm to find the second-largest key among n keys. You can do better than 2n − 3 comparisons.

Have two items, which store the maximum two keys. Scan the array once, keeping track of the maximum and the second maximum item, replacing them as necessary. This takes $2n$ comparisons at most.

(b) Then, give an efficient algorithm to find the third-largest key among n keys. How many key comparisons does your algorithm do in the worst case? Must your algorithm determine which key is largest and second-largest in the process?

The same algorithm as above, but keeping three keys. This takes $3n$ comparisons at most. At some point, quickselect, which averages about $5n$ comparisons would be better.

### Quicksort

4-21. Use the partitioning idea of quicksort to give an algorithm that finds the
median element of an array of n integers in expected O(n) time. (Hint: must
you look at both sides of the partition?)

You can create quickselect, which finds the median (midpoint) of the array in $O(n)$ expected time. You would choose some random pivot, then all items that are smaller than the set would go to the left, all items that are the same stay, and the items that are larger go to the right. If `len(left + center) == mid` then you can terminate with the current item. Otherwise, if there are too few items, recurse into the right side. Otherwise, recurse into the left side.

4-22. The median of a set of n values is the $n/2th$ smallest value.
(a) Suppose quicksort always pivoted on the median of the current sub-array.
How many comparisons would quicksort make then in the worst case?

Quicksort would make $log n$ comparisons in the worst case.

(b) Suppose quicksort always pivoted on the $n/3th$ smallest value of the
current sub-array. How many comparisons would be made then in the
worst case?

This would make $log_3 n$ comparisons in the worst case.

4-23. Suppose an array A consists of n elements, each of which is red, white, or
blue. We seek to sort the elements so that all the reds come before all the whites,
which come before all the blues. The only operations permitted on the keys are:

- Examine(A,i) – report the color of the ith element of A.
- Swap(A,i,j) – swap the ith element of A with the jth element.

Find a correct and efficient algorithm for red–white–blue sorting. There is a
linear-time solution.

First pass: group red elements from 0 to k. Swapping not red elements found from begin and red elements found from end.

Second pass: group white elements from k to j. Swapping not white elements from k and white elements from end.

Blue elements already grouped from j to n.

4-24. Give an efficient algorithm to rearrange an array of n keys so that all
the negative keys precede all the non-negative keys. Your algorithm must be
in-place, meaning you cannot allocate another array to temporarily hold the
items. How fast is your algorithm?

The algorithm would start with two pointers, one at the start and one at the end.

There are four possible cases:

1. $$ start \lt 0 & end \lt 0 $$
2. $$ start \lt 0 & end \gte 0 $$
3. $$ start \gte 0 & end \gte 0 $$
4. $$ start \gte 0 & end \lt 0 $$

In the first case, since both items are negative, we increment the start pointer to the next item.
In the second case, both items are correctly sorted, so we increment the start pointer and decrement the end pointer.
In the third case, both items are greater than zero. We want to decrement the end pointer, since it is in the correct location.
In the fourth case, neither item is in the right place. We swap them then increment the start pointer and decrement the end pointer.

We do this in a loop until the array is partitioned properly.

This takes $O(n)$ time.

4-25. Consider a given pair of different elements in an input array to be sorted,
say zi and zj . What is the most number of times zi and zj might be compared
with each other during an execution of quicksort?

If unfortunate, $O(n)$ times. On average case it is $O(log n)$ times.

4-26. Define the recursion depth of quicksort as the maximum number of successive
recursive calls it makes before hitting the base case. What are the minimum
and maximum possible recursion depths for randomized quicksort?

For quicksort, the minimum times is 1, and the maximum times is $O(n)$. For randomized quicksort, the average case is $O(log n)$.

4-27. Suppose you are given a permutation p of the integers 1 to n, and seek
to sort them to be in increasing order $[1,\dots,n]$. The only operation at your
disposal is reverse(p,i,j), which reverses the elements of a subsequence $pi,\dots,pj$
in the permutation. For the permutation $[1, 4, 3, 2, 5]$ one reversal (of the second
through fourth elements) suffices to sort.

(a) Show that it is possible to sort any permutation using O(n) reversals.

???

(b) Now suppose that the cost of reverse(p,i,j) is equal to its length, the num-
ber of elements in the range, |j − i| + 1. Design an algorithm that sorts p
in O(n log n) cost. Analyze the running time and cost of your algorithm
and prove correctness.

???

### Mergesort

4-28. Consider the following modification to merge sort: divide the input array
into thirds (rather than halves), recursively sort each third, and finally combine
the results using a three-way merge subroutine. What is the worst-case running
time of this modified merge sort?

It is $O(n log_3 n)$, which is on the order of $O(n log_2 n)$.

4-29. Suppose you are given k sorted arrays, each with n elements, and you want
to combine them into a single sorted array of $kn$ elements. One approach is to
use the merge subroutine repeatedly, merging the first two arrays, then merging
the result with the third array, then with the fourth array, and so on until you
merge in the kth and final input array. What is the running time?

This is $O(nk)$, since merging two arrays of length $m$ and $n$ takes $O(max(m + n))$, and this is repeated $k$ times.

4-30. Consider again the problem of merging k sorted length-n arrays into a single
sorted length-kn array. Consider the algorithm that first divides the k arrays
into k/2 pairs of arrays, and uses the merge subroutine to combine each pair,
resulting in k/2 sorted length-2n arrays. The algorithm repeats this step until
there is only one length-kn sorted array. What is the running time as a function
of n and k?

This has a runtime of $O(n * k)$ as well, since splitting the arrays into pairs does not affect the runtime.

### Other Sorting Algorithms

4-31. Stable sorting algorithms leave equal-key items in the same relative order
as in the original permutation. Explain what must be done to ensure that
mergesort is a stable sorting algorithm.

To keep mergesort stable, we also need to keep the indices of the items while sorting.
If two of the same item are encountered, then ties are broken with their indexes.

4-32. Wiggle sort: Given an unsorted array A, reorder it such that $A[0] \lt A[1] \gt A[2] \lt A[3]$
For example, one possible answer for input $[3, 1, 4, 2, 6, 5]$ is
$[1, 3, 2, 5, 4, 6]$. Can you do it in $O(n)$ time using only $O(1)$ space?

```python
def wiggle_sort(nums: List[int]) -> List[int]:
    for i in range(len(nums)):
        if (i % 2 == 1) == (nums[i - 1] > nums[i]):
            nums[i - 1], nums[i] = nums[i], nums[i - 1]

    return nums
```

4-33. Show that n positive integers in the range 1 to k can be sorted in O(n log k)
time. The interesting case is when $k \ll n$.

To do this, we first allocate an array of length $k - 1$. Then for every item in $n$, we place it in its index. This allows us to sort in $O(n)$ time.

For a $k$ that is larger, we might first divide the numbers by some constant and put them into buckets and sort those buckets, like radix sort. Radix sort only works if $n$ is polynomially bounded by $k$.

4-34. Consider a sequence $S$ of $n$ integers with many duplications, such that the
number of distinct integers in $S$ is $O(log n)$. Give an $O(n log log n)$ worst-case
time algorithm to sort such sequences.

Assuming we could allocate a buffer of $O(log n)$, we could create a sorted map that maps key -> count of the distinct integers. First, we iterate through the array with count $n$ and then populate the sorted map. Then, we iterate through the sorted map in order, populating the resulting array with the result in $O(n log log n)$ time.

4-35. Let $A[1,\dots,n]$ be an array such that the first $n \minus \sqrt{n}$ elements are already sorted (though we know nothing about the remaining elements). Give an algorithm that sorts A in substantially better than n log n steps.

We would split the array into its sorted part, calling this $m$, and the unsorted part, calling this $n$. We would add the entire unsorted part $n$ into a heap, and then the first element of the sorted list. We would pop from the heap and replace pops with items from the sorted part. This would terminate in faster than $O(n log n)$ steps.

4-36. Assume that the array $A[1..n]$ only has numbers from ${1,\dots,n^2}$ but that
at most $log log n$ of these numbers ever appear. Devise an algorithm that sorts
A in substantially less than $O(n log n)$.

Since $log log n$ is very small, we can allocate a sorted map of that size. As we iterate through the array, we increment the count of each item that we find in the array. At the end, we can iterate through the map in sorted order, in $O (n log log n)$ time.

4-37. Consider the problem of sorting a sequence of n 0’s and 1’s using comparisons.
For each comparison of two values x and y, the algorithm learns which of
`x < y, x = y`, or `x > y` holds.

(a) Give an algorithm to sort in n − 1 comparisons in the worst case. Show
that your algorithm is optimal.

The simplest algorithm is to count the amount of 0s and 1s and repopulate the array with the count of 0s then 1s.
With comparisons, we could compare the first element with 0. If it's equal, we know its 0, if it's greater, then 1. Then we compare the next element, recursively. If we find a 0, we keep it in its current location, and with a 1, swap it to the end.

(b) Give an algorithm to sort in $2n/3$ comparisons in the average case (assuming each of the n inputs is 0 or 1 with equal probability).
Show that your algorithm is optimal.

Recursively compare neighbors. If they are equal, then you require more comparisons. For the ones that are unequal, you require no more comparisons. This can be done in $1/2 + 1/4... 1/n$ comparisons, or $2n/3$ comparisons.

4-38. Let P be a simple, but not necessarily convex, n-sided polygon and q an
arbitrary point not necessarily in P. Design an efficient algorithm to find a line
segment originating from q that intersects the maximum number of edges of P.
In other words, if standing at point q, in what direction should you aim a gun
so the bullet will go through the largest number of walls. A bullet through a
vertex of P gets credit for only one wall. An $O(n log n)$ algorithm is possible.

???

### Lower Bounds

4-39. In one of my research papers [Ski88], I discovered a comparison-based sorting
algorithm that runs in $O(n log(\sqrt{n}))$. Given the existence of an $Ω(n log n)$ lower
bound for sorting, how can this be possible?

$O(n log \sqrt{n})$ reduces to $O(n log n)$, so this does not violate the lower bound on comparison sorts.

4-40. Mr. B. C. Dull claims to have developed a new data structure for priority
queues that supports the operations Insert, Maximum, and Extract-Max—all in
$O(1)$ worst-case time. Prove that he is mistaken. (Hint: the argument does not
involve a lot of gory details—just think about what this would imply about the
$Ω(n log n)$ lower bound for sorting.

If Insert, Maximum, and Extract-Max were all supported in $O(1)$, always, then we could sort in $O(n)$ time.

One way to think about it is we would take an unsorted array, $N$ with length $n$, and then insert all the items into the data structure.
Then, we would call Extract-Max on it $n$ times, to get back the sorted array in two passes, or $O(n)$ time. This would violate the lower bound on sorting.

### Searching

4-41. A company database consists of 10,000 sorted names, 40% of whom are
known as good customers and who together account for 60% of the accesses to
the database. There are two data structure options to consider for representing
the database:
(a) Put all the names in a single array and use binary search.
(b) Put the good customers in one array and the rest of them in a second array. Only if we do not find the query name on a binary search of the first array do we do a binary search of the second array.

Demonstrate which option gives better expected performance. Does this change if linear search on an unsorted array is used instead of binary search for both options?

We can find out which one is better with a little math.

Either $log_2 10000$ is better than a hit on $log_2 4000$ 60% of the time with a fallback to $log_2 6000$ 40% of the time.

So:

$log_2 10000$ is ~13.

$log_2 4000$ is ~12 and $log_2 6000$ is ~12.5.

So, 60% of the time, the access time is $\lt 12$, and 40% of the time, the access time is $\lt 24.5$, so the expected worse case access time is (6/10 * 12) + (4/10 * 24.5) or ~17. So the second approach is worse by about 30% or so.

The worst + average case analysis is about the same.

If linear search is used, then the math changes:

Either $10000$ access or $4000$ accesses 60% of the time or $10000$ access 40% of the time.

The second approach would be better in this case.

4-42. A Ramanujan number can be written two different ways as the sum of two
cubes—meaning there exist distinct positive integers $a$, $b$, $c$, and $d$ such that
$a^3 + b^3 = c^3 + d^3$. For example, 1729 is a Ramanujan number because $1729 =
1^3 + 12^3 = 9^3 + 10^3$.

(a) Give an efficient algorithm to test whether a given single integer n is a
Ramanujan number, with an analysis of the algorithm’s complexity.

The objective is to find two cubes that sum to the target number, $n$. To do so, we could first take the cube root of the number $n$, and call this $r$ . This provides an upper bound to the search space of integers. Then, for all numbers from $1,\dots,r$ we find all pairs in $O(n^2)$ time that sum to the number $n$. However, with a rearrangement of the equation, we can lower the time.

$$n - r^3 = x^3$$

By rewriting the equation, for each number from $1,\dots,r$ we can subtract it from $n$ and then take that number's cube root. If it results in an integer, we have find one pair. We just need to be careful to deduplicate since we will encounter it twice. This would take $O(\sqrt[3]{n})$ time, where $n$ is the number provided, assuming cube roots can be found in $O(1)$ time.

(b) Now give an efficient algorithm to generate all the Ramanujan numbers between 1 and n, with an analysis of its complexity

To do this for all numbers from 1 and n, I would first calculate all the cube roots from $1,\dots,\sqrt[3]{n}$ and put them in a hashmap (as a lookup table). Then I would access that table when finding the Ramanujan numbers.

Prev: [data-structures](data-structures.md)
Next: [divide-and-conquer](divide-and-conquer.md)
