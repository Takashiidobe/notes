---
title: "Similarity Search"
pdf: "[[03-similarity-search.pdf]]"
---

# Similarity Search

Prev: [[02-property-preserving-lossy-compression]]
Next: [[04-curse-of-dimensionality]]

Similarity search involves the basic problem of organizing a dataset so that similar items can be found quickly.

There are two common framings of this question:

1. All the data is present, and one wants to find pairs or sets of similar items from within the dataset.

2. There is a reference dataset that one has plenty of time to process cleverly, but when were are given a new datapoint, we want to quickly return a similar datapoint from the reference dataset.

There are many real world applications for this:

- Similar documents, web pages, genomes, deduplication, plagariasm detection, finding similar genes or chemicals.
- Collaborative filtering: find similar products based on some characteristics.
- Machine Learning/classification
- Combining Datasets
- Fast Labeling

## Measures of Similarity

### Jaccard Similarity

Jaccard similarity, denoted by $J(.,.)$ is a distance metric between two sets, $S$, and $T$.

$$J(S, T) = \frac{S \cap T}{S \cup T}$$

We can represent sets as vectors as well.

Jaccard similarity works well in practice for sparse data. For example, representing documents in terms of the multiset of words they contain works well with Jaccard similarity. As well, for similar customers (e.g. Amazon/Netflix) it works well.

### Euclidean Distance / $l_{2}$ distance, and $l_{p}$ distance

Given datapoints in $\Bbb R^d$, the euclidean distance metric is:

$$D_{euclidean}(x, y) = \left\Vert x - y \right\Vert_{2} = \sqrt{(x(i) - y(i))^2}$$

As well, Euclidean distance is rotationally invariant (the value does not change when arbitrary rotations are applied to it).

This is a pretty good metric, but this requires that your axes mean something.

### Other similarity metrics

Other metrics include "cosine similarity", the similarity of two vectors, edit distance, etc.

### The Relationships Between Metrics, and Metric Embeddings

Given a set of points, and a distance metric $D$, is it possible to map the points into a set of points in $\Bbb R^d$, such that the distance between points is approximated by the euclidean distance?

Formally, given a distance metric $D$, a set of points $X = x_{1},\dots,x_{n}$, is it possible to map the points to a set $Y = y_{1}\dots,y_{n}$ where $y_{i} \in \Bbb R^d$, where for all $i, j$,

$$D(x_{i},x_{j})\approx \left\Vert y_{i} - y_{j} \right\Vert_2$$

This is called "metric embedding", an embedding in $\Bbb R^d$ under euclidean distance.

## A Data Structure for Similarity Search: KD-trees

A KD-tree allows one to quickly find the closest point in a dataset to a given query point. It works pretty well as long as the dimensionality of the space isn't $\gt 20$. A KD-tree is like a binary search tree that partitions space.

Each node will contain the index of a dimension, $i_{v}$, and a value $m_{v}$.

- When inserting a value, choose a dimension from $i \in \{1,\dots,d\}$
- Fix $m$ as the median of the $ith$ dimension of the points. $m = median(x_{1}(i),\dots,x_{n}(i))$. Store dimension $i$ and median $m$ at node $v$. Partition the set $S$ into $S_{\lt}$ and $S_{\gt}$, according to whether the $ith$ coordinate of each point exceeds m.
- Make two children of $v_{\lt}$ and $v_{\gt}$, and recurse on both children.

The tree will have linear size to the initial set of points, and have a depth of $O(log{}n)$.

To find the closest node to a given node $v$, we first traverse the tree and find the leaf that $v$ would end up in. We then backtrack through the tree, at each juncture, asking if the closest point to $v$ would've ended up down the other path.

In low dimensions, the answer will be no, and the search will be efficient. However, for higher dimensions, this answer is more likely than not maybe, which makes the search less efficient.

## The Curse of Dimensionality

Many algorithms have a running time that scales exponentially with the dimension. This is because higher dimensional spaces lack geometry. They have lots and lots of points where the points have roughly the same distance.

Example: What is the largest number of points that fit in $d$-dimensional space, that have pairwise distances of $[0.75, 1]$?

If $d$ = 1: At most 2.
If $d$ = 2: At most 3 points.
If $d$ = 100: At least several thousand.

Prev: [[02-property-preserving-lossy-compression]]
Next: [[04-curse-of-dimensionality]]
