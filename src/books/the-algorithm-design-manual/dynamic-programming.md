---
title: "Dynamic Programming"
---

# Dynamic Programming

Prev: [combinatorial-search](combinatorial-search.md)
Next: [np-completeness](np-completeness.md)

10-1.  Up to k steps in a single bound! A child is running up a staircase with n
steps and can hop between 1 and k steps at a time. Design an algorithm to
count how many possible ways the child can run up the stairs, as a function of
n and k. What is the running time of your algorithm?

10-2.  Imagine you are a professional thief who plans to rob houses along a street
of n homes. You know the loot at house i is worth mi, for 1 ≤ i ≤ n, but you
cannot rob neighboring houses because their connected security systems will
automatically contact the police if two adjacent houses are broken into. Give an
efficient algorithm to determine the maximum amount of money you can steal
without alerting the police.

10-3.  Basketball games are a sequence of 2-point shots, 3-point shots, and 1-
point free throws. Give an algorithm that computes how many possible mixes
(1s,2s,3s) of scoring add up to a given n. For n = 5 there are four possible
solutions: (5, 0, 0), (2, 0, 1), (1, 2, 0), and (0, 1, 1).

We can generate the sequences by noticing the ways to construct 1, 2, 3 points.

10-4. Basketball games are a sequence of 2-point shots, 3-point shots, and 1-point
free throws. Give an algorithm that computes how many possible scoring se-
quences add up to a given n. For n = 5 there are thirteen possible sequences,
including 1-2-1-1, 3-2, and 1-1-1-1-1.

10-5. Given an s × t grid filled with non-negative numbers, find a path from top
left to bottom right that minimizes the sum of all numbers along its path. You
can only move either down or right at any point in time.

Prev: [combinatorial-search](combinatorial-search.md)
Next: [np-completeness](np-completeness.md)
