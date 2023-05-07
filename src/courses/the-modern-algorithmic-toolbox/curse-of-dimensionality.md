---
title: "Curse of Dimensionality"
---

# Curse of Dimensionality

Prev: [similarity-search](similarity-search.md)
Next: [generalization](generalization.md)

The curse of dimensionality, where the time to query the nearest neighbor scales exponentially to the number of dimensions, seems to be fundamental to the problem of nearest neighbors.

For a better intution why: imagine we sort points on a 1D line. Well, to find the nearest neighbor, you have to go either left or right. In a 2D graph, you have four directions to check. In 3D, eight.

$$directions = 2^D$$

1. 1D -> 2
2. 2D -> 4
3. 3D -> 8
4. 4D -> 16

Every known solution that uses a reasonable amount of space uses time exponential to $k$, the number of dimensions, or linearly to $n$, the number of points.

We have to resort to approximation.

## Point of Lecture

The curse of dimensionality is a problem, because the natural representation of data is high-dimensional. Document similarity has $k$ dimensions to the number of unique words in the text -- tens of thousands, maybe millions. Images are represented as real vectors, which one dimension per pixel (so millions to billions). The same holds true for shoppers on amazon or viewers on netflix.

But we can't solve problems in high dimensions well, so we have to employ **dimensionality reduction**, representing points in high-dimensional space as points in lower-dimensional space, preserving interpoint distances as much as possible, so our calculations in lower-dimension space aren't that far off.

## Role Model: Fingerprints

Imagine that for objects that have no notion of distance outside of "equal" and "non-equal". How do we represent them with fewer bits, but with the same relation of equality preserved?

One way is to just hash each item to a 32-bit hash, but that takes 32-bits of memory.

One way to do better is to hash each item, then mod it by 2, so the result takes 1 bit (0 or 1).

$$f(x) = h(x) \text{ mod } 2$$

The properties of the mapping are:

1. If $x = y$, then $f(x) = f(y)$. Thus, equality is preserved.
2. If $x \neq y$, and $h$ is a good hash function, then $chance(f(x) = f(y)) \le \frac{1}{2}$.

So, there's a 50% error of equality. However, for a better accuracy rate, we use more hash functions.

If we repeat the experiment $l$ times, choosing a different hash functions from $h \in h_{1},\dots,h_{l}$, and labeling each object $x$ with $l$ bits consisting of $f_{1}(x),\dots,f_{l}(x)$, the properties become:

1. If $x = y$, then $f_{i}(x) = f_{i}(y)$ for all $i = 1,\dots,l$.
2. If $x \neq y$ and the $h_{i}$'s are good and independent hash functions, then $chance(f(x) = f(y)) \le 2^{-l}$.

To achieve an error rate of $\delta \gt 0$, we only need $\log_{2}\frac{1}{\delta}$ bits to represent each object.

## $L_{2}$ Distance and Random Projections

The fingerprinting subroutine above approximately preserves a 0-1 function on object pairs (equality). What about distances between object pairs? What's the analog of a hash for the euclidean distance?

$$\sqrt{\displaystyle \sum_{i=1}^k(x_{i}-y_{i})^2}$$

The high level idea involves **random project**, which results in the **Johnson-Lindenstrauss** (JL) transform, which says that if we only care about the euclidean distance, we can assume the number of dimensions is only in the hundreds.

### High-level Idea



Prev: [similarity-search](similarity-search.md)
Next: [generalization](generalization.md)
