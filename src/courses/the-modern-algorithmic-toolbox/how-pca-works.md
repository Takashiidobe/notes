---
title: "How PCA works"
---

# How PCA works

Prev: [understanding-principal-component-analysis](understanding-principal-component-analysis.md)
Next: [low-rank-matrix-approximations](low-rank-matrix-approximations.md)

## Introduction

PCA computes the k-dimensional subspace through the origin for a given data set that minimizes the average squared distance between the points and the subspace. This is the same as maximizing the variance of the projections of the data points on the subspace.

## Characterizing Principal Components

### The Setup

The input to PCA is $n$ $d$-dimensional data points, $x_1,\dots, x_n \in \Bbb R^d$ and a parameter $k \in \{1,2,\dots,d\}$. Assuming the data is centered, so that


Prev: [understanding-principal-component-analysis](understanding-principal-component-analysis.md)
Next: [low-rank-matrix-approximations](low-rank-matrix-approximations.md)
