---
title: Weighted Graph Algorithms
date created: Wednesday, November 15th 2023, 6:01:29 pm
date modified: Thursday, July 24th 2025, 10:20:42 pm
---

# Weighted Graph Algorithms

Prev: [graph-traversal](graph-traversal.md)
Next: [combinatorial-search](combinatorial-search.md)

## 8.8 Exercises

### Simulating Graph Algorithms

**8-1.** [3] For the graphs in Problem 7-1:

- (a) Draw the spanning forest after every iteration of the main loop in Kruskal’s algorithm.
    
- (b) Draw the spanning forest after every iteration of the main loop in Prim’s algorithm.
    
- (c) Find the shortest-path spanning tree rooted in A.
    
- (d) Compute the maximum flow from A to H.
    

### Minimum Spanning Trees

**8-2.** [3] Is the path between two vertices in a minimum spanning tree necessarily a shortest path between the two vertices in the full graph? Give a proof or a counterexample.

**8-3.** [3] Assume that all edges in the graph have distinct edge weights. Is the path between a pair of vertices in a minimum spanning tree necessarily a shortest path between the two vertices in the full graph? Give a proof or a counterexample.

**8-4.** [3] Can Prim’s and Kruskal’s algorithms yield different minimum spanning trees? Explain why or why not.

**8-5.** [3] Does either Prim’s or Kruskal’s algorithm work if there are negative edge weights? Explain why or why not.

**8-6.** [3]

- (a) Assume that all edges in the graph have distinct edge weights. Is the minimum spanning tree of this graph unique? Give a proof or a counterexample.
    
- (b) Again, assume that all edges in the graph have distinct edge weights. Is the shortest-path spanning tree of this graph unique? Give a proof or a counterexample.
    

**8-7.** [5] Suppose we are given the minimum spanning tree $T$ of a given graph $G$ (with $n$ vertices and $m$ edges) and a new edge $e = (u, v)$ of weight $w$ that we will add to $G$. Give an efficient algorithm to find the minimum spanning tree of the graph $G + e$. Your algorithm should run in $O(n)$ time.

**8-8.** [5]

- (a) Let $T$ be a minimum spanning tree of a weighted graph $G$. Construct a new graph $G'$ by adding a weight of $k$ to every edge of $G$. Do the edges of $T$ form a minimum spanning tree of $G'$? Prove the statement or give a counterexample.
    
- (b) Let $P = {s, \dots, t}$ describe a shortest path between vertices $s$ and $t$ of a weighted graph $G$. Construct a new graph $G'$ by adding a weight of $k$ to every edge of $G$. Does $P$ describe a shortest path from $s$ to $t$ in $G'$? Prove the statement or give a counterexample.
    

**8-9.** [5] Devise and analyze an algorithm that takes a weighted graph $G$ and finds the smallest change in the cost to a non-minimum spanning tree edge that would cause a change in the minimum spanning tree of $G$. Your algorithm must be correct and run in polynomial time.

**8-10.** [4] Consider the problem of finding a minimum-weight connected subset $T$ of edges from a weighted connected graph $G$. The weight of $T$ is the sum of all the edge weights in $T$.

- (a) Why is this problem not just the minimum spanning tree problem? (Hint: think negative weight edges.)
    
- (b) Give an efficient algorithm to compute the minimum-weight connected subset $T$.
    

**8-11.** [5] Let $T = (V, E')$ be a minimum spanning tree of a given graph $G = (V, E)$ with positive edge weights. Now suppose the weight of a particular edge $e \in E$ is modified from $w(e)$ to a new value $\hat{w}(e)$. We seek to update the minimum spanning tree $T$ to reflect this change without recomputing the entire tree from scratch. For each of the following four cases, give a linear-time algorithm to update the tree:

- (a) $e \notin E'$ and $\hat{w}(e) > w(e)$
    
- (b) $e \notin E'$ and $\hat{w}(e) < w(e)$
    
- (c) $e \in E'$ and $\hat{w}(e) < w(e)$
    
- (d) $e \in E'$ and $\hat{w}(e) > w(e)$
    

**8-12.** [4] Let $G = (V, E)$ be an undirected graph. A set $F \subseteq E$ of edges is called a feedback-edge set if every cycle of $G$ has at least one edge in $F$.

- (a) Suppose that $G$ is unweighted. Design an efficient algorithm to find a minimum-size feedback-edge set.
    
- (b) Suppose that $G$ is a weighted undirected graph with positive edge weights. Design an efficient algorithm to find a minimum-weight feedback-edge set.
    

### Union–Find

**8-13.** [5] Devise an efficient data structure to handle the following operations on a weighted directed graph:

- (a) Merge two given components.
    
- (b) Locate which component contains a given vertex $v$.
    
- (c) Retrieve a minimum edge from a given component.
    

**8-14.** [5] Design a data structure that enables a sequence of $m$ union and find operations on a universal set of $n$ elements, consisting of a sequence of all unions followed by a sequence of all finds, to be performed in time $O(m + n)$.

### Shortest Paths

**8-15.** [3] The single-destination shortest-path problem for a directed graph seeks the shortest path from every vertex to a specified vertex $v$. Give an efficient algorithm to solve the single-destination shortest-path problem.

**8-16.** [3] Let $G = (V, E)$ be an undirected weighted graph, and let $T$ be the shortest-path spanning tree rooted at a vertex $v$. Suppose now that all the edge weights in $G$ are increased by a constant number $k$. Is $T$ still the shortest-path spanning tree from $v$?

**8-17.** [3]

- (a) Give an example of a weighted connected graph $G = (V, E)$ and a vertex $v$, such that the minimum spanning tree of $G$ is the same as the shortest-path spanning tree rooted at $v$.
    
- (b) Give an example of a weighted connected directed graph $G = (V, E)$ and a vertex $v$, such that the minimum spanning tree of $G$ is very different from the shortest-path spanning tree rooted at $v$.
    
- (c) Can the two trees be completely disjoint?
    

**8-18.** [3] Either prove the following or give a counterexample:

- (a) Is the path between a pair of vertices in a minimum spanning tree of an undirected graph necessarily the shortest (minimum-weight) path?
    
- (b) Suppose that the minimum spanning tree of the graph is unique. Is the path between a pair of vertices in a minimum spanning tree of an undirected graph necessarily the shortest (minimum-weight) path?
    

**8-19.** [3] Give an efficient algorithm to find the shortest path from $x$ to $y$ in an undirected weighted graph $G = (V, E)$ with positive edge weights, subject to the constraint that this path must pass through a particular vertex $z$.

**8-20.** [5] In certain graph problems, vertices can have weights instead of or in addition to the weights of edges. Let $C_v$ be the cost of vertex $v$, and $C(x,y)$ the cost of the edge $(x, y)$. This problem is concerned with finding the cheapest path between vertices $a$ and $b$ in a graph $G$. The cost of a path is the sum of the costs of the edges and vertices encountered on the path.

- (a) Suppose that each edge in the graph has a weight of zero (while non-edges have a cost of $\infty$). Assume that $C_v = 1$ for all vertices $1 \le v \le n$. Give an efficient algorithm to find the cheapest path from $a$ to $b$ and its time complexity.
    
- (b) Now suppose that the vertex costs are not constant (but are all positive) and the edge costs remain as above. Give an efficient algorithm to find the cheapest path from $a$ to $b$ and its time complexity.
    
- (c) Now suppose that both the edge and vertex costs are not constant (but are all positive). Give an efficient algorithm to find the cheapest path from $a$ to $b$ and its time complexity.
    

**8-21.** [5] Give an $O(n^3)$ algorithm that takes an $n$-vertex directed graph $G$ with positive edge lengths, and returns the length of the shortest cycle in the graph. This length is $\infty$ in the case of an acyclic graph.

**8-22.** [5] A highway network is represented by a weighted graph $G$, with edges corresponding to roads and vertices corresponding to road intersections. Each road is labeled with the maximum possible height of vehicles that can pass through the road. Give an efficient algorithm to compute the maximum possible height of vehicles that can successfully travel from $s$ to $t$. What is the runtime of your algorithm?

**8-23.** [5] You are given a directed graph $G$ with possibly negative weighted edges, in which the shortest path between any two vertices is guaranteed to have at most $k$ edges. Give an algorithm that finds the shortest path between two vertices $u$ and $v$ in $O(k \cdot (n + m))$ time.

**8-24.** [5] Can we solve the single-source longest-path problem by changing minimum to maximum in Dijkstra’s algorithm? If so, then prove your algorithm correct. If not, then provide a counterexample.

**8-25.** [5] Let $G = (V, E)$ be a weighted acyclic directed graph with possibly negative edge weights. Design a linear-time algorithm to solve the single-source shortest-path problem from a given source $v$.

**8-26.** [5] Let $G = (V, E)$ be a directed weighted graph such that all the weights are positive. Let $v$ and $w$ be two vertices in $G$ and $k \le |V|$ be an integer. Design an algorithm to find the shortest path from $v$ to $w$ that contains exactly $k$ edges. Note that the path need not be simple.

**8-27.** [5] Arbitrage is the use of discrepancies in currency-exchange rates to make a profit. For example, there may be a small window of time during which:

- 1 U.S. dollar buys 0.75 British pounds,
    
- 1 British pound buys 2 Australian dollars,
    
- and 1 Australian dollar buys 0.70 U.S. dollars.
    

At such a time, a smart trader can trade one U.S. dollar and end up with:

$$0.75×2×0.7=1.05 U.S. dollars0.75 \times 2 \times 0.7 = 1.05 \text{ U.S. dollars}$$

—a profit of 5%.

Suppose that there are $n$ currencies $c_1, \dots, c_n$ and an $n \times n$ table $R$ of exchange rates, such that one unit of currency $c_i$ buys $R[i, j]$ units of currency $c_j$. Devise and analyze an algorithm to determine the maximum value of:

$$R[c1,ci1]⋅R[ci1,ci2]⋅⋯⋅R[cik−1,cik]⋅R[cik,c1]R[c_1, c_{i_1}] \cdot R[c_{i_1}, c_{i_2}] \cdot \dots \cdot R[c_{i_{k-1}}, c_{i_k}] \cdot R[c_{i_k}, c_1]$$

(Hint: think all-pairs shortest path.)

### Network Flow and Matching

**8-28.** [3] A matching in a graph is a set of disjoint edges—that is, edges that do not have common vertices. Give a linear-time algorithm to find a maximum matching in a tree.

**8-29.** [5] An edge cover of an undirected graph $G = (V, E)$ is a set of edges such that each vertex in the graph is incident to at least one edge from the set. Give an efficient algorithm, based on matching, to find the minimum-size edge cover for $G$.

Prev: [graph-traversal](graph-traversal.md)
Next: [combinatorial-search](combinatorial-search.md)
