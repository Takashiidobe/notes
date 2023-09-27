---
title: "Graphs as matrices and the Laplacian of a graph"
---

# Graphs as matrices and the Laplacian of a graph

Prev: [tensor-methods](tensor-methods.md)
Next: [spectral-techniques](spectral-techniques.md)

Spectral graph theory is the theory that arises from the following:

1. Represent the graph as a matrix
2. Study the eigenvectors/eigenvalues of the matrix

These notes consider undirected unweighted graphs that don't have self-loops.

## Graphs as Matrices

Given a graph, $G = (V,E) with \bar V \bar = n$ vertices, the Laplacian matrix associated to $G$ is the $n x n$ matrix $L_G = D - A$ where $D$ is the degree matrix, a diagonal matrix where $D(i,i)$ is the degree of the $i$th node in $G$ and $A$ is the adjacency matrix, with $A(i,j) = 1$ iff $(i, j) \in E$. So:

$$ L_G(i, j) = \begin{cases} deg(i) & if i = j \\ -1 & if (i, j) \in E \\ 0 & otherwise \end{cases} $$

For ease of notation, the laplacian will be referred to as $L$.


Prev: [tensor-methods](tensor-methods.md)
Next: [spectral-techniques](spectral-techniques.md)
