---
title: NP-Completeness
date created: Wednesday, November 15th 2023, 6:01:29 pm
date modified: Thursday, July 24th 2025, 10:27:16 pm
---

# NP-Completeness

Prev: [dynamic-programming](dynamic-programming.md)
Next: [dealing-with-hard-problems](dealing-with-hard-problems.md)

## 11.10 Exercises

### Transformations and Satisfiability

**11-1.** [2] Apply the reduction from SAT to 3-SAT for the formula:  
$(x∨y∨z∨w∨u∨v)∧(x∨y∨z∨w∨u∨v)∧(x∨y∨z∨w∨u∨v)∧(x∨y)(x \lor y \lor z \lor w \lor u \lor v) \land (x \lor y \lor z \lor w \lor u \lor v) \land (x \lor y \lor z \lor w \lor u \lor v) \land (x \lor y)$

**11-2.** [3] Draw the graph resulting from reducing the 3-SAT formula:  
$(x∨y∨z)∧(x∨y∨z)∧(x∨y∨z)∧(x∨y∨x)(x \lor y \lor z) \land (x \lor y \lor z) \land (x \lor y \lor z) \land (x \lor y \lor x)$ 
to vertex cover.

**11-3.** [3] Prove that 4-SAT is NP-hard.

**11-4.** [3] Prove that Stingy SAT (find a satisfying assignment where at most $k$ variables are true) is NP-hard.

**11-5.** [3] Show that Double SAT (existence of at least two different satisfying assignments) is NP-hard.

**11-6.** [4] Suppose we have a subroutine solving the TSP decision problem in linear time. Give an efficient algorithm to construct the actual TSP tour using polynomial calls to this subroutine.

**11-7.** [7] Implement a SAT-to-3SAT reduction that transforms any SAT instance into an equivalent 3-SAT instance.

**11-8.** [7] Design and implement a backtracking algorithm to test whether a set of clauses is satisfiable. What pruning criteria can be applied?

**11-9.** [8] Implement the vertex cover to SAT reduction. Run the resulting clauses through a SAT solver. Evaluate the practicality of this approach.

### Basic Reductions

**11-10.** [4] Prove that Set Cover is NP-hard by reducing Vertex Cover to it.

**11-11.** [4] Prove that the Baseball Card Collector problem is NP-hard by reduction from Vertex Cover.

**11-12.** [4]

- (a) Prove that the Low-Degree Spanning Tree problem is NP-hard via reduction from Hamiltonian Path.
    
- (b) For the High-Degree Spanning Tree problem (maximize degree), give an efficient algorithm and analyze its time complexity.
    

**11-13.** [5] Minimum Element Set Cover:

- (a) Show that $C = {{1,2,3}, {1,3,4}, {2,3,4}, {3,4,5}}$ has a cover of size 6 but none of size 5.
    
- (b) Prove the problem is NP-hard.
    

**11-14.** [3] Prove that the Half-Hamiltonian Cycle problem (existence of a cycle of length $\lfloor n/2 \rfloor$) is NP-hard.

**11-15.** [5] Prove that the 3-Phase Power Balance problem (partition integers into three equal-sum subsets) is NP-hard.

**11-16.** [4] Prove that the Dense Subgraph problem is NP-hard.

**11-17.** [4] Prove that the Clique, No-Clique problem is NP-hard.

**11-18.** [5] Prove that computing the number of edges in the largest Eulerian subgraph is NP-hard.

**11-19.** [5] Prove that the Maximum Common Subgraph problem is NP-hard.

**11-20.** [5] Prove that finding a Strongly Independent Set is NP-hard.

**11-21.** [5] Prove that the Max Kite problem is NP-hard.

### Creative Reductions

**11-22.** [5] Prove that the Hitting Set problem is NP-hard.

**11-23.** [5] Prove that the Knapsack decision problem is NP-hard.

**11-24.** [5] Prove that the Hamiltonian Path problem is NP-hard.

**11-25.** [5] Prove that the Longest Path problem is NP-hard.

**11-26.** [6] Prove that the Dominating Set problem is NP-hard.

**11-27.** [7] Prove that Vertex Cover remains NP-hard even when all vertices have even degree.

**11-28.** [7] Prove that the Set Packing problem is NP-hard.

**11-29.** [7] Prove that the Feedback Vertex Set problem is NP-hard.

**11-30.** [8] Describe a reduction from Sudoku to Vertex Coloring. Construct a graph that can be colored with 9 colors if and only if the Sudoku board is solvable.

### Algorithms for Special Cases

**11-31.** [5] Give an $O(n + m)$ algorithm to determine whether a DAG contains a Hamiltonian Path. (Hint: topological sorting.)

**11-32.** [3] Prove that the $k$-Clique problem is efficiently solvable for fixed $k$ (i.e., $k$ is constant).

**11-33.** [8] Give a polynomial-time algorithm to solve 2-SAT (formulas in 2-CNF).

### P = NP?

**11-34.** [4] Show that the following problems are in NP:

- Simple path of length $k$ in graph $G$
    
- Is integer $n$ composite?
    
- Vertex cover of size $k$ in graph $G$
    

**11-35.** [7] Why doesn’t the following algorithm prove primality is in $P$ despite running in $O(n)$ time?

```text
PrimalityTesting(n)
  composite = false
  for i := 2 to n - 1 do
    if (n mod i) = 0 then
      composite = true
```

Prev: [dynamic-programming](dynamic-programming.md)
Next: [dealing-with-hard-problems](dealing-with-hard-problems.md)
