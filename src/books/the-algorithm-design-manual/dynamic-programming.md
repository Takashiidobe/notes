---
title: Dynamic Programming
date created: Saturday, November 18th 2023, 4:49:17 pm
date modified: Thursday, July 24th 2025, 10:25:40 pm
---

# Dynamic Programming

Prev: [combinatorial-search](combinatorial-search.md)
Next: [np-completeness](np-completeness.md)

## 10.11 Exercises

### Elementary Recurrences

**10-1.** [3] A child is running up a staircase with $n$ steps and can hop between $1$ and $k$ steps at a time. Design an algorithm to count how many possible ways the child can run up the stairs, as a function of $n$ and $k$. What is the running time of your algorithm?

**10-2.** [3] You plan to rob $n$ houses along a street. The loot at house $i$ is worth $m_i$, but you cannot rob neighboring houses. Give an efficient algorithm to determine the maximum amount of money you can steal.

**10-3.** [5] Basketball scoring involves 1-, 2-, and 3-point shots. Give an algorithm that computes how many possible combinations add up to a given $n$. E.g., for $n = 5$ there are four mixes: $(5, 0, 0)$, $(2, 0, 1)$, $(1, 2, 0)$, $(0, 1, 1)$.

**10-4.** [5] Compute how many scoring sequences (order matters) add up to a given $n$ using 1-, 2-, and 3-point scores. For $n = 5$, there are thirteen such sequences.

**10-5.** [5] Given an $s \times t$ grid of non-negative numbers, find a path from top-left to bottom-right that minimizes the sum of numbers along the path. You can move only down or right.

- (a) Solve with Dijkstra's algorithm. Analyze time complexity.
    
- (b) Solve with dynamic programming. Analyze time complexity.
    

### Edit Distance

**10-6.** [3] Incorporate a swap operation (transposition of adjacent characters) into the edit distance function so that such errors cost one operation.

**10-7.** [4] Given strings $X$, $Y$, and $Z$ such that $|X| = n$, $|Y| = m$, and $|Z| = n + m$, determine if $Z$ is a shuffle of $X$ and $Y$ (i.e., maintains character order).

- (a) Show that `cchocohilaptes` is a shuffle of `chocolate` and `chips`.
    
- (b) Give a DP algorithm to decide if $Z$ is a shuffle.
    

**10-8.** [4] Find the longest common substring (not subsequence) of two strings $X$ and $Y$.

- (a) Give a $\Theta(nm)$ DP algorithm based on edit distance.
    
- (b) Give a simpler $\Theta(nm)$ algorithm without DP.
    

**10-9.** [6] Let $T$ and $P$ be two sequences. Let $LCS(T, P)$ and $SCS(T, P)$ denote the longest common subsequence and shortest common supersequence.

- (a) Give efficient algorithms to compute both.
    
- (b) Prove $d(T, P) = |SCS| - |LCS|$, where $d$ is the edit distance with only insertions and deletions.
    

**10-10.** [5] You are given two stacks of poker chips, each chip colored. In a move, you choose a color and remove all top chips of that color. Goal: remove all chips in fewest moves. Give an $O(n^2)$ DP algorithm.

### Greedy Algorithms

**10-11.** [4] Let $P_1, \dots, P_n$ be $n$ programs with sizes $s_i$ and a disk of size $D$.

- (a) Does greedy selection by smallest $s_i$ maximize number of programs stored?
    
- (b) Does greedy selection by largest $s_i$ maximize disk usage?
    

**10-12.** [5] Given coin denominations ${d_1, \dots, d_k}$:

- (a) Show greedy does not always minimize number of coins (e.g., ${1,6,10}$).
    
- (b) Give an efficient DP algorithm to compute minimum coins to make change for $n$.
    

**10-13.** [5] Count the number of distinct ways $C(n)$ to make change of $n$ units with denominations ${d_1, \dots, d_k}$.

- (a) How many ways to make 20 from ${1, 6, 10}$?
    
- (b) Give an efficient algorithm and analyze its time.
    

**10-14.** [6] Given $n$ jobs each with processing time $t_i$ and deadline $d_i$, show that scheduling by earliest deadline yields a feasible schedule if one exists.

### Number Problems

**10-15.** [3] Rod cutting problem: maximize value from cutting a rod of length $n$, given prices for each length. Give a DP solution.

**10-16.** [5] Maximize value of an arithmetic expression with $n$ terms by parenthesizing. E.g., $6 + 2 \times 0 - 4$.

**10-17.** [5] Compute the smallest number of perfect squares that sum to $n$. Give an efficient DP algorithm.

**10-18.** [5] Find the largest sum of a contiguous subarray in $A = [a_1, \dots, a_n]$.

**10-19.** [5] Partition $m$ suitcases of weight $w_i$ into two subsets of equal total weight.

**10-20.** [6] Solve the subset sum problem (knapsack): find a subset of $S$ summing to $T$ in $O(nT)$ time.

**10-21.** [6] Solve the integer partition problem: partition $S$ into two subsets with equal sum in $O(nM)$ time.

**10-22.** [5] Given numbers on a circle, find the max contiguous sum along any arc.

**10-23.** [5] Given positions to break a string, determine break order to minimize total cost. DP algorithm in $O(n^3)$ time.

**10-24.** [5] Given dictionary of $m$ strings (each of length $\le k$), find best way to encode string $D$ of length $n$ using fewest substrings. Design $O(nmk)$ algorithm.

**10-25.** [5] Chess match: 24 games. Champion keeps title in case of tie. Games have probabilities depending on color.

- (a) Write a recurrence for champion’s retention probability.
    
- (b) Implement DP algorithm.
    
- (c) Analyze time complexity.
    

**10-26.** [8] Egg drop: find floor $f$ where egg breaks. Let $E(k, n)$ be min drops with $k$ eggs and $n$ floors.

- (a) Show $E(1, n) = n$.
    
- (b) Show $E(k, n) = \Theta(n^{1/k})$.
    
- (c) Give recurrence and DP algorithm.
    

### Graph Problems

**10-27.** [4] Given $X \times Y$ grid with "bad" intersections:

- (a) Give example where no path exists.
    
- (b) $O(XY)$ algorithm to find any path avoiding bad cells.
    
- (c) $O(XY)$ algorithm to find shortest path.
    

**10-28.** [5] In same grid setting, count number of safe paths of length $X + Y - 2$. Algorithm must run in $O(XY)$.

**10-29.** [5] Stack boxes where each box must be strictly smaller than the one below in width, height, and depth. Maximize stack height.

### Design Problems

**10-30.** [4] Books of fixed height $h$ on shelves of length $L$. Show greedy packing minimizes number of shelves. Analyze time.

**10-31.** [6] Books of varying height. Shelf height is max height of any book on it.

- Show greedy doesn't minimize height.
    
- Give DP algorithm and analyze time.
    

**10-32.** [5] Given linear keyboard of $k$ keys, and starting finger positions, type string of length $n$ with minimal total finger movement. DP algorithm.

**10-33.** [5] You know the future price of stock over $n$ days. One transaction per day. Maximize profit under constraints.

**10-34.** [8] Given compressed string $S$ with no spaces:

- (a) Use dict($w$) to determine if $S$ can be split into words. $O(n^2)$ time.
    
- (b) If dict is a set of $m$ words of max length $\ell$, give an efficient solution.
    

**10-35.** [8] Two-player digit game: starting from $n$-digit number $N$, each player alternates taking first or last digit to maximize their score. Give optimal DP strategy for player 1.

**10-36.** [6] Maximum contiguous subarray sum:

- Give $\Theta(n^2)$ algorithm.
    
- Then give $\Theta(n)$ DP algorithm. Partial credit: $O(n \log n)$ divide-and-conquer.
    

**10-37.** [7] Given string $x = x_1 \dots x_n$ over $k$-symbol alphabet and a multiplication table, decide if you can parenthesize to evaluate to symbol $a$. Multiplication is non-commutative and non-associative. Polynomial time algorithm in $n$ and $k$.

**10-38.** [6] Given keys $k_1, \dots, k_n$ and query probabilities $p_1, \dots, p_n$, and cost $\alpha$ (left), $\beta$ (right), build BST with optimal expected query cost.

### Interview Problems

**10-39.** [5] Given coin denominations, find the minimum number of coins to make a given amount.

**10-40.** [5] Given array of $n$ numbers (positive, negative, or zero), find indices $i$ and $j$ to get max sum in subarray $[i, j]$.

**10-41.** [7] Can you construct a string using cut-out letters from a magazine, where cutting one letter also removes the reverse side? Assume a function gives you the reverse letter/position. Give an algorithm to decide if target string can be formed.

Prev: [combinatorial-search](combinatorial-search.md)
Next: [np-completeness](np-completeness.md)
