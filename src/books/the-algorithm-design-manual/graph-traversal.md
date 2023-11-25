---
title: "Graph Traversal"
---

# Graph Traversal

Prev: [hashing-and-randomized-algorithms](hashing-and-randomized-algorithms.md)
Next: [weighted-graph-algorithms](weighted-graph-algorithms.md)

## Exercises

### Simulating Graph Algorithms

7-1. For the following weighted graphs $G_1$ (left) and $G_2$ (right):

(a) Report the order of the vertices encountered on a breadth-first search starting
from vertex A. Break all ties by picking the vertices in alphabetical
order (i.e. A before Z).

(b) Report the order of the vertices encountered on a depth-first search starting
from vertex A. Break all ties by picking the vertices in alphabetical order
(i.e. A before Z).

$G_1$:

BFS:
A -> B -> D -> I -> C -> E -> G -> J -> F -> H
DFS:
A -> B -> C -> E -> D -> G -> H -> F -> J -> I

$G_2$:

BFS:
A -> B -> E -> C -> F -> I -> D -> G -> J -> M -> H -> K -> N -> L -> O -> P
DFS:
A -> B -> C -> D -> H -> G -> F -> E -> I -> J -> K -> L -> P -> O -> N -> M

7-2. Do a topological sort of the following graph $G$:

A -> B -> C -> F -> E -> G -> I -> J -> D

### Traversal

7-3. Prove that there is a unique path between any pair of vertices in a tree.



7-4. Prove that in a breadth-first search on a undirected graph $G$, every edge is
either a tree edge or a cross edge, where x is neither an ancestor nor descendant
of y in cross edge (x, y).
7-5. Give a linear algorithm to compute the chromatic number of graphs where
each vertex has degree at most 2. Any bipartite graph has a chromatic number
of 2. Must such graphs be bipartite?
7-6. You are given a connected, undirected graph G with n vertices and m edges.
Give an $O(n + m)$ algorithm to identify an edge you can remove from G while
still leaving G connected, if one exists. Can you reduce the running time to
O(n)?
7-7. In breadth-first and depth-first search, an undiscovered node is marked discovered
when it is first encountered, and marked processed when it has been
completely searched. At any given moment, several nodes might be simultaneously
in the discovered state.
(a) Describe a graph on n vertices and a particular starting vertex v such that
Θ(n) nodes are simultaneously in the discovered state during a breadth-first
search starting from v.
(b) Describe a graph on n vertices and a particular starting vertex v such that
Θ(n) nodes are simultaneously in the discovered state during a depth-first search
starting from v.
(c) Describe a graph on n vertices and a particular starting vertex v such that
at some point Θ(n) nodes remain undiscovered, while Θ(n) nodes have been
processed during a depth-first search starting from v. (Hint: there may also be
discovered nodes.)

7-8. Given pre-order and in-order traversals of a binary tree (discussed in Section
3.4.1), is it possible to reconstruct the tree? If so, sketch an algorithm to do it.
If not, give a counterexample. Repeat the problem if you are given the pre-order
and post-order traversals.

With preorder and inorder traversals:

```python
def buildTree(self, preorder: List[int], inorder: List[int]) -> Optional[TreeNode]:
    if inorder and preorder:
        pos = inorder.index(preorder[0])
        root = TreeNode(preorder[0])
        root.left = self.buildTree(preorder[1:pos+1],inorder[:pos])
        root.right = self.buildTree(preorder[pos+1:], inorder[pos+1:])
        return root
```

With preorder and postorder traversals:

```python
def buildTree(self, preorder: List[int], postorder: List[int]) -> Optional[TreeNode]:
    root = TreeNode(postorder.pop())
    if root.val != preorder[-1]:
        root.right = self.constructFromPrePost(preorder, postorder)
    if root.val != preorder[-1]:
        root.left = self.constructFromPrePost(preorder, postorder)
    preorder.pop()
    return root
```

7-9. Present correct and efficient algorithms to convert an undirected graph $G$
between the following graph data structures. Give the time complexity of each
algorithm, assuming n vertices and m edges.

(a) Convert from an adjacency matrix to adjacency lists.

(b) Convert from an adjacency list representation to an incidence matrix. An
incidence matrix M has a row for each vertex and a column for each edge,
such that M [i, j] = 1 if vertex i is part of edge j, otherwise M [i, j] = 0.

(c) Convert from an incidence matrix to adjacency lists.

7-10. Suppose an arithmetic expression is given as a tree. Each leaf is an integer
and each internal node is one of the standard arithmetical operations (+, −, ∗, /).
For example, the expression 2+3*4+(3*4)/5 is represented by the tree in Figure 17.

(a). Give an O(n) algorithm for evaluating such an expression, where there
are $n$ nodes in the tree.

Each internal node (an operation) has either an integer (if said node is a leaf) or an operation that, when all of its children have been evaluated, can be evaluated into an integer.

Starting with the root node:
If it is an integer: return that integer.
Otherwise, call evaluate on its children.

```python
def evaluate(root: ExprNode) -> int:
    if root.is_int():
        return root.val
    if root.is_operation():
        if root.operation() == "*":
            return evaluate(root.left) * evaluate(root.right)
        if root.operation() == "/":
            return evaluate(root.left) / evaluate(root.right)
        if root.operation() == "-":
            return evaluate(root.left) - evaluate(root.right)
        if root.operation() == "+":
            return evaluate(root.left) + evaluate(root.right)
```

7-11. Suppose an arithmetic expression is given as a DAG (directed acyclic graph)
with common subexpressions removed. Each leaf is an integer and each internal
node is one of the standard arithmetical operations (+, −, ∗, /). For example, the
expression 2+3*4+(3*4)/5 is represented by the DAG in Figure 7.17(b). Give
an O(n + m) algorithm for evaluating such a DAG, where there are n nodes and
m edges in the DAG. (Hint: modify an algorithm for the tree case to achieve
the desired efficiency.)

Similar to the above, skipping.

7-12. The war story of Section 7.4 (page 210) describes an algorithm for construct-
ing the dual graph of the triangulation efficiently, although it does not guarantee
linear time. Give a worst-case linear algorithm for the problem.

### Applications

7-13. The Chutes and Ladders game has a board with n cells where you seek to
travel from cell 1 to cell n. To move, a player throws a six-sided dice to determine
how many cells forward they move. This board also contains chutes and ladders
that connect certain pairs of cells. A player who lands on the mouth of a chute
immediately falls back down to the cell at the other end. A player who lands on
the base of a ladder immediately travels up to the cell at the top of the ladder.
Suppose you have rigged the dice to give you full control of the number for each
roll. Give an efficient algorithm to find the minimum number of dice throws to
win.

Assuming that a chute always moves you backwards and ladders move you forwards.
I would start at the end and traverse backwards, by climbing down ladders and climbing up chutes.
Then, we would backtrack. I would mark each end of a ladder with the position at the start of the ladder. For each choice, I would backtrack and see what is the optimal path all the way to the start. This requires exponential time, so we could have a cache that stores the "fastest" time to get to a square. Any path that is on the same square but took more steps is automatically slower, so it can be pruned.

7-14. Plum blossom poles are a Kung Fu training technique, consisting of n large
posts partially sunk into the ground, with each pole $p_i$ at position ($x_i$, $y_i$).
Students practice martial arts techniques by stepping from the top of one pole to
the top of another pole. In order to keep balance, each step must be more than
d meters but less than 2d meters. Give an efficient algorithm to find a safe path
from pole $p_s$ to $p_t$ if it exists.

Since a person could go between poles, but that would just complicate the implementation, assume that we cannot go backwards to any pole we've already visited. We would do dfs or bfs on all possible paths, and maintain a visited set so we don't explore any paths we have already visited.

7-15. You are planning the seating arrangement for a wedding given a list of guests,
$V$. For each guest $g$ you have a list of all other guests who are on bad terms
with them. Feelings are reciprocal: if $h$ is on bad terms with $g$, then $g$ is on bad
terms with $h$. Your goal is to arrange the seating such that no pair of guests
sitting at the same table are on bad terms with each other. There will be only
two tables at the wedding. Give an efficient algorithm to find an acceptable
seating arrangement if one exists.

This algorithm is whether or not the guest list can be turned into a bipartite graph.
This can be simplified into a cycle algorithm: If one guest, $g_i$ dislikes another guest, $g_j$,
then they can not sit at the same table. However, if $g_j$ dislikes another guest, $g_k$ and $g_k$ also dislikes $g_i$, then there is a cycle that requires at least three tables, instead of two, so we cannot allocate a bipartite graph.
To create an efficient algorithm to see if an acceptable seating arrangement exists:

While maintaining a visited set, $S$:

1. Take any guest, $g_i$
2. Add $g_i$ to the visited set.
3. Visit all of the nodes that $g_i$ dislikes, adding it to $S$.
4. Visit all of the nodes that $g_i$'s neighbors dislikes, adding it to $S$.
5. If there is a cycle back to $g_i$, return false.
6. If not, take any random unvisited guest from $g$ and continue until all guests are visited.
7. If all guests are visited without there being a cycle, return true.

### Algorithm Design

7-16. The square of a directed graph $G = (V, E)$ is the graph $G_2 = (V, E_2)$ such
that $(u, w) \in E2$ iff there exists $v \in V$ such that $(u, v) \in E$ and $(v, w) \in E$; that
is, there is a path of exactly two edges from $u$ to $w$.
Give efficient algorithms for both adjacency lists and matrices.



7-17. A vertex cover of a graph G = (V, E) is a subset of vertices V ′ such that
each edge in E is incident to at least one vertex of V ′.
(a) Give an efficient algorithm to find a minimum-size vertex cover if G is a
tree.
(b) Let G = (V, E) be a tree such that the weight of each vertex is equal to the
degree of that vertex. Give an efficient algorithm to find a minimum-weight
vertex cover of G.
(c) Let G = (V, E) be a tree with arbitrary weights associated with the ver-
tices. Give an efficient algorithm to find a minimum-weight vertex cover
of G.
7-18. A vertex cover of a graph G = (V, E) is a subset of vertices V ′ such that each
edge in E is incident to at least one vertex of V ′. Delete all the leaves from any
depth-first search tree of G. Must the remaining vertices form a vertex cover of
G? Give a proof or a counterexample.
7-19. [5] An independent set of an undirected graph G = (V, E) is a set of vertices U
such that no edge in E is incident to two vertices of U .
(a) Give an efficient algorithm to find a maximum-size independent set if G is
a tree.
(b) Let G = (V, E) be a tree with weights associated with the vertices such
that the weight of each vertex is equal to the degree of that vertex. Give
an efficient algorithm to find a maximum-weight independent set of G.
(c) Let G = (V, E) be a tree with arbitrary weights associated with the ver-
tices. Give an efficient algorithm to find a maximum-weight independent
set of G.
7-20. [5] A vertex cover of a graph G = (V, E) is a subset of vertices V ′ such that
each edge in E is incident on at least one vertex of V ′. An independent set of
graph G = (V, E) is a subset of vertices V ′ ∈ V such that no edge in E contains
both vertices from V ′.
An independent vertex cover is a subset of vertices that is both an independent
set and a vertex cover of G. Give an efficient algorithm for testing whether G
contains an independent vertex cover. What classical graph problem does this
reduce to?
7-21. [5] Consider the problem of determining whether a given undirected graph G =
(V, E) contains a triangle, that is, a cycle of length 3.
(a) Give an O(|V |3) algorithm to find a triangle if one exists.
(b) Improve your algorithm to run in time O(|V | · |E|). You may assume
|V | ≤ |E|.
Observe that these bounds give you time to convert between the adjacency
matrix and adjacency list representations of G.
7-22. [5] Consider a set of movies M1, M2, . . . , Mk . There is a set of customers,
each one of which indicates the two movies they would like to see this weekend.
Movies are shown on Saturday evening and Sunday evening. Multiple movies
may be screened at the same time.
You must decide which movies should be televised on Saturday and which on
Sunday, so that every customer gets to see the two movies they desire. Is there a
schedule where each movie is shown at most once? Design an efficient algorithm
to find such a schedule if one exists.
7-23. [5] The diameter of a tree T = (V, E) is given by
max
u,v∈V δ(u, v)
(where δ(u, v) is the number of edges on the path from u to v). Describe an
efficient algorithm to compute the diameter of a tree, and show the correctness
and analyze the running time of your algorithm.
7-24. [5] Given an undirected graph G with n vertices and m edges, and an integer k,
give an O(m + n) algorithm that finds the maximum induced subgraph F of G
such that each vertex in F has degree ≥ k, or prove that no such graph exists.
Graph F = (U, R) is an induced subgraph of graph G = (V, E) if its vertex set
U is a subset of the vertex set V of G, and R consists of all edges of G whose
endpoints are in U .
7-25. [6] Let v and w be two vertices in an unweighted directed graph G = (V, E).
Design a linear-time algorithm to find the number of different shortest paths
(not necessarily vertex disjoint) between v and w.
7-26. [6] Design a linear-time algorithm to eliminate each vertex v of degree 2 from
a graph by replacing edges (u, v) and (v, w) by an edge (u, w). It should also
eliminate multiple copies of edges by replacing them with a single edge. Note
that removing multiple copies of an edge may create a new vertex of degree 2,
which has to be removed, and that removing a vertex of degree 2 may create
multiple edges, which also must be removed.

### Directed Graphs

7-27. The reverse of a directed graph $G = (V, E)$ is another directed graph
$GR = (V, E_R)$ on the same vertex set, but with all edges reversed; that is,
$ER = {(v, u) : (u, v) \in E}$. Give an $O(n + m)$ algorithm for computing the
reverse of an n-vertex m-edge graph in adjacency list format.

7-28. Your job is to arrange n ill-behaved children in a straight line, facing front.
You are given a list of m statements of the form "i hates j." If i hates j, then
you do not want to put i somewhere behind j, because then i is capable of
throwing something at j.

(a) Give an algorithm that orders the line (or says that it is not possible) in
$O(m + n)$ time.

This is flattening a directed graph into a linked list, thus any ordering with cycles is not valid.
What we could do is visit the list of $m$ statements that state that $i$ hates $j$, and see if there is any cycle where $i$ is disliked again after recursing through all of $i$'s dislikes. We repeat this for all other children who have dislikes. If no cycle is produced, the children are orderable.

(b) Suppose instead you want to arrange the children in rows such that if $i$
hates $j$, then $i$ must be in a lower numbered row than $j$. Give an efficient
algorithm to find the minimum number of rows needed, if it is possible.

7-29. A particular academic program has n required courses, certain pairs of which
have prerequisite relations so that (x, y) means you must take course x before
y. How would you analyze the prerequisite pairs to make sure it is possible for
people to complete the program?

This is a topological sort problem.

I would allocate two things: a queue that processes courses that are now eligible to visit, and a dictionary of nodes -> prerequisites.
As well, a reverse mapping of prerequisites -> nodes.

While there are courses that are eligible to take (first with courses without prerequisites), and then adding in courses that have prerequisites filled.

If we ever run out of courses without taking them all, the program is not completable. Otherwise, it is, and the order processed through the queue is a valid ordering.

7-30. Gotcha-solitaire is a game on a deck with n distinct cards (all face up) and
m gotcha pairs (i, j) such that card i must be played sometime before card j.
You play by sequentially choosing cards, and win if you pick up the entire deck
without violating any gotcha pair constraints. Give an efficient algorithm to
find a winning pickup order if one exists.

7-31. You are given a list of n words each of length k in a language you don’t know,
although you are told that words are sorted in lexicographic (alphabetical) order.
Reconstruct the order of the $\alpha$ alphabet letters (characters) in that language.
For example, if the strings are ${QQZ, QZZ, XQZ, XQX, XXX}$, the character
order must be Q before Z before X.
(a) Give an algorithm to efficiently reconstruct this character order. (Hint: use
a graph structure, where each node represents one letter.)
(b) What is its running time, as a function of n, k, and α?

7-32. A weakly connected component in a directed graph is a connected component
ignoring the direction of the edges. Adding a single directed edge to a
directed graph can reduce the number of weakly connected components, but by
at most how many components? What about the number of strongly connected
components?

1. Adding a single directed edge can reduce the number of weakly connected components by at most 1.
2. Adding a single directed edge can reduce the number of strongly connected components by at most 1.

7-33. Design a linear-time algorithm that, given an undirected graph $G$ and a
particular edge $e$ in it, determines whether $G$ has a cycle containing $e$.

Start off at $e$, and allocate a visited set, $S$. Visit all of $e$'s neighbors recursively. Ignore any previously visited nodes. If any node revisits $e$, then return true. Otherwise, return false.

7-34. An arborescence of a directed graph G is a rooted tree such that there is a
directed path from the root to every other vertex in the graph. Give an efficient
and correct algorithm to test whether G contains an arborescence, and its time
complexity.


7-35. A mother vertex in a directed graph G = (V, E) is a vertex v such that all
other vertices G can be reached by a directed path from v.
(a) Give an O(n + m) algorithm to test whether a given vertex v is a mother
of G, where n = |V| and m = |E|.
(b) Give an O(n + m) algorithm to test whether graph G contains a mother
vertex.

7-36. Let G be a directed graph. We say that G is k-cyclic if every (not necessarily
simple) cycle in G contains at most k distinct nodes. Give a linear-time algo-
rithm to determine if a directed graph G is k-cyclic, where G and k are given
as inputs. Justify the correctness and running time of your algorithm.

7-37. A tournament is a directed graph formed by taking the complete undirected
graph and assigning arbitrary directions on the edges—that is, a graph G =
(V, E) such that for all u,v ∈ V , exactly one of (u, v) or (v, u) is in E. Show
that every tournament has a Hamiltonian path—that is, a path that visits every
vertex exactly once. Give an algorithm to find this path.

### Articulation Vertices

7-38. An articulation vertex of a connected graph $G$ is a vertex whose deletion
disconnects $G$. Let $G$ be a graph with $n$ vertices and $m$ edges. Give a simple
$O(n + m)$ algorithm for finding a vertex of $G$ that is not an articulation vertex—
that is, whose deletion does not disconnect $G$.

1. Visit every vertex, $n_i$. For each vertex, keep track of its indegrees and outdegrees.
If there is a vertex with 1 indegree and 0 outdegrees, then it can be removed immediately.
Otherwise, if there is a vertex who's outdegrees are all redundant, such that another set of vertices have outdegrees to those vertices, then that vertex can be removed as well.

7-39. Following up on the previous problem, give an $O(n + m)$ algorithm that finds
a deletion order for the $n$ vertices such that no deletion disconnects the graph.
(Hint: think DFS/BFS.)

One thought would be to think about a topological sort. We add any nodes that have 0 outdegrees first, since they can be disconnected immediately. Then, for each vertex we delete, we decrement the count of outdegrees of the existing vertices in the graph by one. If we have any more outdegrees that are now zero, we decrement those, and then continue on. If we can no longer remove a node, and the graph still contains vertices, return false. Otherwise, return true.

7-40. Suppose $G$ is a connected undirected graph. An edge $e$ whose removal dis-
connects the graph is called a bridge. Must every bridge $e$ be an edge in a
depth-first search tree of $G$? Give a proof or a counterexample.

In a DFS of a connected undirected graph, each vertex must be an edge in a depth-first search tree of $G$.

7-41. A city that only has two-way streets has decided to change them all into one-
way streets. They want to ensure that the new network is strongly connected
so everyone can legally drive anywhere in the city and back.

(a) Let $G$ be the original undirected graph. Prove that there is a way to
properly orient/direct the edges of $G$ provided $G$ does not contain a bridge.

Since we're turning an undirected graph to a directed one, every vertex used to have one indegree and outdegree to connect to the other vertices. If the graph is now directed, each node must now have at least two edges, one indegree and one outdegree, to connect it to the rest of the graph. If there is a bridge, where there is only one edge connecting a given node, $n_i$ to the rest of the graph, then it cannot be reconnected to the rest of the graph, as there is either no way to leave the vertex or no way to enter it (since there could only be one indegree or one outdegree).

(b) Give an efficient algorithm to orient the edges of a bridgeless graph $G$ so
the result is strongly connected.

To give an algorithm: we start off with an arbitrary vertex, $n_i$ in $G$. Then, we traverse through the graph and orient all edges in the direction of the traversal, ignoring any edges that would take us to a vertex already encountered.
For any other edges that haven't been oriented yet, we point them to the starting vertex, since that vertex can reach all other vertices. Since there are no bridges, any vertex can reach a vertex that can make its way back to the starting vertex, thus, all vertices are reachable.

### Interview Problems

7-42. Which data structures are used in depth-first and breath-first search?

In depth-first search, a stack (either stack frames or an explicit stack) and in breadth-first search, a queue.

7-43. Write a function to traverse binary search tree and return the ith node in sorted order.

One way is to do a normal in-order traversal and just return the $ith$ item:

```python
def ith_smallest(self, root: Optional[TreeNode], i: int) -> int:
    def traverse(node):
        if node:
            yield from traverse(node.left)
            yield node.val
            yield from traverse(node.right)
    return next(itertools.islice(traverse(root), i, None))
```

Prev: [hashing-and-randomized-algorithms](hashing-and-randomized-algorithms.md)
Next: [weighted-graph-algorithms](weighted-graph-algorithms.md)
