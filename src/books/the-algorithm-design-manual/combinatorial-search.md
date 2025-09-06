---
title: Combinatorial Search
date created: Wednesday, November 15th 2023, 6:01:29 pm
date modified: Thursday, July 24th 2025, 10:23:40 pm
---

# Combinatorial Search

Prev: [weighted-graph-algorithms](weighted-graph-algorithms.md)
Next: [dynamic-programming](dynamic-programming.md)

## 9.8 Exercises

### Permutations

**9-1.** [3] A derangement is a permutation $p$ of ${1, \dots, n}$ such that no item is in its proper position, that is, $p_i \ne i$ for all $1 \le i \le n$. Write an efficient backtracking program with pruning that constructs all the derangements of $n$ items.

**9-2.** [4] Multisets are allowed to have repeated elements. A multiset of $n$ items may thus have fewer than $n!$ distinct permutations. For example, ${1, 1, 2, 2}$ has only six distinct permutations: $[1,1,2,2]$, $[1,2,1,2]$, $[1,2,2,1]$, $[2,1,1,2]$, $[2,1,2,1]$, and $[2,2,1,1]$. Design and implement an efficient algorithm for constructing all permutations of a multiset.

**9-3.** [5] For a given positive integer $n$, find all permutations of the $2n$ elements of the multiset $S = {1, 1, 2, 2, \dots, n, n}$ such that for each integer from $1$ to $n$ the number of intervening elements between its two appearances is equal to the value of the element. For example, when $n = 3$ the two possible solutions are $[3,1,2,1,3,2]$ and $[2,3,1,2,1,3]$.

**9-4.** [5] Design and implement an algorithm for testing whether two graphs are isomorphic. The graph isomorphism problem is discussed in Section 19.9. With proper pruning, graphs on hundreds of vertices can be tested in a reasonable time.

**9-5.** [5] The set ${1,2,3,\dots,n}$ contains a total of $n!$ distinct permutations. By listing and labeling all of the permutations in ascending lexicographic order, we get the following sequence for $n=3$:  
$[123,132,213,231,312,321]$. Give an efficient algorithm that returns the $k$th of $n!$ permutations in this sequence, for inputs $n$ and $k$. For efficiency, it should not construct the first $k - 1$ permutations in the process.

### Backtracking

**9-6.** [5] Generate all structurally distinct binary search trees that store values $1$ to $n$, for a given value of $n$.

**9-7.** [5] Implement an algorithm to print all valid (meaning properly opened and closed) sequences of $n$ pairs of parentheses.

**9-8.** [5] Generate all possible topological orderings of a given DAG.

**9-9.** [5] Given a specified total $t$ and a multiset $S$ of $n$ integers, find all distinct subsets from $S$ whose elements add up to $t$. For example, if $t = 4$ and $S = {4, 3, 2, 2, 1, 1}$, then the different sums that equal $t$ include: $4$, $3+1$, $2+2$, and $2+1+1$. A number can be used within a sum up to the number of times it appears in $S$, and a single number counts as a sum.

**9-10.** [8] Design and implement an algorithm for solving the subgraph isomorphism problem—given graphs $G$ and $H$, does there exist a subgraph $H'$ of $H$ such that $G$ is isomorphic to $H'$? Report how your program performs on such special cases of subgraph isomorphism as Hamiltonian cycle, clique, independent set, and graph isomorphism.

**9-11.** [5] A team assignment of $n = 2k$ players is a partitioning of them into two teams with exactly $k$ people per team. For example, if the players are named ${A, B, C, D}$, there are three distinct ways to partition them into two equal teams: ${{A,B},{C,D}}$, ${{A,C},{B,D}}$, and ${{A,D},{B,C}}$.

- (a) List the 10 possible team assignments for $n = 6$ players.
    
- (b) Give an efficient backtracking algorithm to construct all possible team assignments. Be sure to avoid repeating any solution.
    

**9-12.** [5] Given an alphabet $\Sigma$, a set of forbidden strings $S$, and a target length $n$, give an algorithm to construct a string of length $n$ on $\Sigma$ without any element of $S$ as a substring. For $\Sigma = {0,1}$, $S = {01, 10}$, and $n=4$, the two possible solutions are `0000` and `1111`. For $S = {0,11}$ and $n=4$, no such string exists.

**9-13.** [5] In the $k$-partition problem, we need to partition a multiset of positive integers into $k$ disjoint subsets that have equal sum. Design and implement an algorithm for solving the $k$-partition problem.

**9-14.** [5] You are given a weighted directed graph $G$ with $n$ vertices and $m$ edges. The mean weight of a cycle is the sum of its edge weights divided by the number of its edges. Find a cycle in $G$ of minimum mean weight.

**9-15.** [8] In the turnpike reconstruction problem, you are given a multiset $D$ of $n(n-1)/2$ distances. The problem is to place $n$ points on the line such that their pairwise distances are $D$. For example, the distances $D = {1, 2, 3, 4, 5, 6}$ can be obtained by placing the second point 1 unit from the first, the third point 3 from the second, and the fourth point 2 from the third. Design and implement an efficient algorithm to find all solutions to the turnpike reconstruction problem.

### Games and Puzzles

**9-16.** [5] Anagrams are rearrangements of the letters of a word or phrase into a different word or phrase. For example, “MANY VOTED BUSH RETIRED” is an anagram of “TUESDAY NOVEMBER THIRD.” Design and implement an algorithm for finding anagrams using combinatorial search and a dictionary.

**9-17.** [5] Construct all sequences of moves that a knight on an $n \times n$ chessboard can make where the knight visits every square only once.

**9-18.** [5] A Boggle board is an $n \times m$ grid of characters. For a given board, we seek to find all possible words that can be formed by a sequence of adjacent characters on the board, without repetition. For example, the board:

```
e t h t
n d t i
a i h n
r h u b
```

contains words like "tide", "dent", "raid", and "hide". Design an algorithm to construct the most words for a given board $B$ consistent with a dictionary $D$.

**9-19.** [5] A Babbage square is a grid of words that reads the same across as it does down. Given a $k$-letter word $w$ and a dictionary of $n$ words, find all Babbage squares starting with that word.

**9-20.** [5] Show that you can solve any given Sudoku puzzle by finding the minimum vertex coloring of a specific, appropriately constructed $9 \times 9 + 9$ vertex graph.

### Combinatorial Optimization

For problems **9-21** to **9-27**, implement a combinatorial search program to solve it for small instances. How well does your program perform in practice?

**9-21.** [5] Design and implement an algorithm for solving the bandwidth minimization problem (Section 16.2).

**9-22.** [5] Design and implement an algorithm for solving the maximum satisfiability problem (Section 17.10).

**9-23.** [5] Design and implement an algorithm for solving the maximum clique problem (Section 19.1).

**9-24.** [5] Design and implement an algorithm for solving the minimum vertex coloring problem (Section 19.7).

**9-25.** [5] Design and implement an algorithm for solving the minimum edge coloring problem (Section 19.8).

**9-26.** [5] Design and implement an algorithm for solving the minimum feedback vertex set problem (Section 19.11).

**9-27.** [5] Design and implement an algorithm for solving the set cover problem (Section 21.1).

### Interview Problems

**9-28.** [4] Write a function to find all permutations of the letters in a given string.

**9-29.** [4] Implement an efficient algorithm for listing all $k$-element subsets of $n$ items.

**9-30.** [5] An anagram is a rearrangement of the letters in a given string into a sequence of dictionary words, like "Steven Skiena" into "Vainest Knees". Propose an algorithm to construct all the anagrams of a given string.

**9-31.** [5] Telephone keypads have letters on each numerical key. Write a program that generates all possible words resulting from translating a given digit sequence (e.g. 145345) into letters.

**9-32.** [7] You start with an empty room and a group of $n$ people waiting outside. At each step, you may either admit one person into the room, or let one out. Can you arrange a sequence of $2^n$ steps, so that every possible combination of people is achieved exactly once?

**9-33.** [4] Use a random number generator (rng04) that generates numbers from ${0, 1, 2, 3, 4}$ with equal probability to write a random number generator that generates numbers from $0$ to $7$ (rng07) with equal probability. What is the expected number of calls to rng04 per call of rng07?

Prev: [weighted-graph-algorithms](weighted-graph-algorithms.md)
Next: [dynamic-programming](dynamic-programming.md)
