---
title: "How PCA works"
pdf: "[[08-how-pca-works.pdf]]"
---

# How PCA works

Prev: [[07-understanding-principal-component-analysis]]
Next: [[09-low-rank-matrix-approximations]]

We have $n$ centered data points, and a parameter $k$, which finds a $k$-dimensional subspace through the origin
$$x_1,\dots,x_n \in \mathbb{R}^d$$
And maximizes the variance of the projections:

$$\frac{1}{n} \sum_{i=1}^n \sum_{j=1}^k \langle x_i, v_j \rangle^2$$
Or minimizes average squared distance of points to the $k$-dimensional subspace.

It has a few cons:

- sensitivity to high-variance noise
- **cannot capture non-linear structure**
- components must be orthogonal to interpret

## Characterizing Principal Components




Prev: [[07-understanding-principal-component-analysis]]
Next: [[09-low-rank-matrix-approximations]]
