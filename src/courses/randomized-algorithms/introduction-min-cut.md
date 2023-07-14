---
title: "Introduction; min-cut"
---

# Introduction; min-cut

Next: [concentration-inequalities](concentration-inequalities.md)

## Introduction to Randomized Algorithms

A Randomized Algorithm uses randomness internally.

### Examples of Randomized Algorithms

- Random number generation
- Quicksort
- Random projection
- Randomized Rounding
- K-means
- Hash Tables

### Random Seeds

Random choices used in an algorithm can be considered a "random seed". For any input, the algorithm should work on most seeds. Thus, there can be some seeds where the algorithm does not work well.

### Reasons to use Randomness in an algorithm

- Simplicity
- Speed
- To combat adversarial inputs

Adversarial inputs means undesirable inputs. For example, a presorted list is bad for naive quicksort. That's not malicious, but it's still bad. On the other hand, someone could try to crash your web server by causing hash collisions. that's malicious.

### Uses of randomness in algorithms

- **Fingerprinting**: If we want to compare large items, we could compare their hashes rather than comparing every bit of the full items. This could allow us to find duplicates quickly.

- **Random Sampling**: Approximating arbitrary graphs by sparse graph, e.g. spectral specification. Sampling can be done uniformly at random, or intentionally over-sampling important elements.

- **Load Balancing**: To ensure an equal load for parts of a system.

- **Symmetry breaking**: If computers don't have a random algorithm to talk in a network, they may all try to talk to the same computer, overloading it. This happens a lot in computer networks, so nodes have to have some probabilistic way to choose where to send messages to, lest they break the system.

- **Probabilistic existence proofs**: There are ways to prove the existence of a construction by creating a randomized algorithm that produces it, compared to a deterministic construction. Some examples are expander graph constructions, which are normally randomized, and the Lovasz Local lemma.

### The Lovasz Local Lemma

Consider $n$ events that occur with a low probability, $p \ll 1$. How would we should that there is a non-zero probability that none of them occur? For example, that none of the computers in a network crash.

For independent events, it is $(1 - p)^n) \gt 0$.

For somewhat dependent events, this lemma helps us out.

Given a dependency graph of events, where events are nodes and edges represent dependence between events, with a sparse graph and the nodes having degree of most $d$: the lemma guarantees that if $4pd \lt 1$, the there is a positive probability that no event happens.

With $pd \ge 1$, there could be a clique of $d$ events that are adversarially correlated, so that at least one of them always occurs. If $pd \ge 1$, there is no guarantee of a probability greater than 0 that no event occurs.

### Game Tree Evaluation

Randomized algorithms can sometimes guarantee performance that is impossible to guarantee with deterministic algorithms.

Assuming a binary tree built from the `NOR` function. The leaves contain the iitial input, $\{0, 1\}$ and each non-leaf node contains the output of an `NOR` operation done on its children. This is basically computation. The task is to find the value of the root node, while minimizing the number of leaves that need to be observed in order to find the value of the root, with $n$ being the number of leaves.

1. Any deterministic algorithm will need to look at each of the $n$ leaves to determine the root value in worst case.
2. For a good randomized algorithm, in best case, we need only observe $\sqrt{n}$ leaves.
3. For a good randomized algorithm, with average luck, it will need to check about $n^{0.6}$ leaves.

### Types of Randomized Algorithms

**Las Vegas**:

- always correct
- runtime is random (has chance of being slow)
- Example: Quicksort

**Monte Carlo**:

- runtime is always bounded
- correctness is random (can be wrong)
- Example: Random projection

## The Global Min-Cut Problem

Next: [concentration-inequalities](concentration-inequalities.md)
