---
title: "Divide and Conquer"
---

# Divide and Conquer

Prev: [sorting](sorting.md)
Next: [hashing-and-randomized-algorithms](hashing-and-randomized-algorithms.md)

### Binary Search
5-1. Suppose you are given a sorted array A of size n that has been circularly
shifted k positions to the right. For example, [35, 42, 5, 15, 27, 29] is a sorted
array that has been circularly shifted k = 2 positions, while [27, 29, 35, 42, 5, 15]
has been shifted k = 4 positions.

- Suppose you know what k is. Give an O(1) algorithm to find the largest
number in A.

If you know what `k` is, you either have to look `k` positions after or before the location you'd normally expect it to be.

- Suppose you do not know what k is. Give an O(lg n) algorithm to find the
largest number in A. For partial credit, you may give an $O(n)$ algorithm.

The $O(n)$ algorithm is trivial, by finding the maximum number in the set.

The $O(log n)$ algorithm involves peak finding. By repeatedly binary searching and keeping track of whether the previous iteration was larger or smaller as expected allows us to binary search in the opposite way (if required) to find the maximum element.

5-2. A sorted array of size n contains distinct integers between 1 and n + 1, with
one element missing. Give an $O(log n)$ algorithm to find the missing integer,
without using any extra space.

Binary search through the array. Assume we start at the middle of the array. There are two possibilities:

If the number > i + 1, then the number is on the left hand side. Recurse into the left hand side of the array.

If not, the number is on the right hand side. Recurse into the right hand side of the array.

5-3. Consider the numerical Twenty Questions game. In this game, the first
player thinks of a number in the range 1 to n. The second player has to figure
out this number by asking the fewest number of true/false questions. Assume
that nobody cheats.
(a) What is an optimal strategy if n in known?

Binary search, ask if the number is less or greater than the midpoint of n, recursively. This takes $O(log n)$ time.

(b) What is a good strategy if n is not known?

If n is not known, the same strategy still works. You can still use the same tactic. If you manage to ask two questions where $q_1 \lt n \lt q_2$ then you can immediately get an $O(log n)$ run time. If you can't, then you must settle for an $O(n)$ time, but there is a non-zero chance that you can get the $O(log n)$ run time.

5-4. You are given a unimodal array of n distinct elements, meaning that its
entries are in increasing order up until its maximum element, after which its
elements are in decreasing order. Give an algorithm to compute the maximum
element of a unimodal array that runs in $O(log n)$ time.



5-5. Suppose that you are given a sorted sequence of distinct integers $[a_1,a_2,\dots,a_n]$.
Give an $O(log n)$ algorithm to determine whether there exists an index i such that
$a_i = i$. For example, in $[−10, −3, 3, 5, 7]$, $a3 = 3$. In $[2, 3, 4, 5, 6, 7]$, there is no
such i.

5-6. Suppose that you are given a sorted sequence of distinct integers $a =
[a_1,a_2,\dots, a_n]$, drawn from 1 to m where $n \lt m$. Give an $O(log n)$ algorithm to
find an integer $\le m$ that is not present in a. For full credit, find the smallest
such integer x such that $1 \le x \le m$.

5-7. Let M be an n × m integer matrix in which the entries of each row are
sorted in increasing order (from left to right) and the entries in each column are
in increasing order (from top to bottom). Give an efficient algorithm to find the
position of an integer x in M , or to determine that x is not there. How many
comparisons of x with matrix entries does your algorithm use in worst case?

### Divide and Conquer Algorithms

5-8. Given two sorted arrays A and B of size n and m respectively, find the
median of the n + m elements. The overall run time complexity should be
O(log(m + n)).
5-9. [8] The largest subrange problem, discussed in Section 5.6, takes an array A of
n numbers, and asks for the index pair i and j that maximizes S = ∑j
k=i A[k]. Give an O(n) algorithm for largest subrange.


5-10. [8] We are given n wooden sticks, each of integer length, where the ith piece
has length L[i]. We seek to cut them so that we end up with k pieces of exactly
the same length, in addition to other fragments. Furthermore, we want these k
pieces to be as large as possible.
(a) Given four wood sticks, of lengths $L = {10, 6, 5, 3}$, what are the largest
sized pieces you can get for k = 4? (Hint: the answer is not 3).
(b) Give a correct and efficient algorithm that, for a given L and k, returns the
maximum possible length of the k equal pieces cut from the initial n sticks.

5-11. [8] Extend the convolution-based string-matching algorithm described in the
text to the case of pattern matching with wildcard characters “*”, which match
any character. For example, “sh*t” should match both “shot” and “shut".

### Recurrence Relations
5-12. [5] In Section 5.3, it is asserted that any polynomial can be represented by a
recurrence. Find a recurrence relation that represents the polynomial $a_n = n^2$.

5-13. Suppose you are choosing between the following three algorithms:

- Algorithm A solves problems by dividing them into five subproblems of
half the size, recursively solving each subproblem, and then combining the
solutions in linear time.
- Algorithm B solves problems of size n by recursively solving two subprob-
lems of size n − 1 and then combining the solutions in constant time.
- Algorithm C solves problems of size n by dividing them into nine subprob-
lems of size n/3, recursively solving each subproblem, and then combining
the solutions in $Θ(n^2)$ time.
What are the running times of each of these algorithms (in big O notation), and
which would you choose?
5-14. [5] Solve the following recurrence relations and give a Θ bound for each of them:
(a) T (n) = 2T (n/3) + 1
(b) T (n) = 5T (n/4) + n
(c) T (n) = 7T (n/7) + n
(d) T (n) = 9T (n/3) + n^2
5-15. [3] Use the master theorem to solve the following recurrence relations:
(a) T (n) = 64T (n/4) + n^4
(b) T (n) = 64T (n/4) + n^3
(c) T (n) = 64T (n/4) + 128
5-16. [3] Give asymptotically tight upper (Big Oh) bounds for T (n) in each of the
following recurrences. Justify your solutions by naming the particular case of
the master theorem, by iterating the recurrence, or by using the substitution
method:
(a) T (n) = T (n − 2) + 1.
(b) T (n) = 2T (n/2) + n lg2 n.
(c) T (n) = 9T (n/4) + n2.

Prev: [sorting](sorting.md)
Next: [hashing-and-randomized-algorithms](hashing-and-randomized-algorithms.md)
