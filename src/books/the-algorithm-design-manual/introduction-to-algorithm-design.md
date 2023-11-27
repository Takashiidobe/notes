---
title: "Introduction to Algorithm Design"
---

# Introduction to Algorithm Design

Next: [algorithm-analysis](algorithm-analysis.md)

An algorithm is a procedure to accomplish a specific task.

We want algorithms to be **correct**, **efficient**, and **easy to implement**.

## Robot Tour Optimization

A robot needs to solder a circuit board. It starts out at a starting point, solders all the contact points, and then returns to its starting position to work on the next board. This is called a tour. We want to take a set of points in a plane and return the shortest cycle tour that visits each point.

The Nearest neighbor heuristic (greedy) doesn't work, as there can be an input that trips up the algorithm.

This is the Traveling salesman problem, which is NP-hard. The only correct solution is

## Selecting the Right Jobs

Assume you are an actor that needs to accept a set of jobs, which take some amount of time. You cannot work on two jobs at the same time, so you must choose some non-overlapping set of jobs that make the most amount of money as possible.

There is an efficient algorithm, sorting the input based on its completion date, accepting the job that ends earliest in the set, and continuing recursively.

## Reasoning About Correctness

Always try to narrow down what the input and output of a given problem are. "Best" is subjective, but shortest path/least turns are more objective and thus easier to answer.

Incorrect algorithms can be proven with counterexamples. They should be easy to verify and simple.

Some ways to break algorithms involve:

- Thinking small
- Thinking exhaustively
- Hunting for a weakness
- Going for a tie
- Using extremes

## Induction and Recursion

Lots of algorithms can be proven to work properly on inductively, where they work on some base cases and can work on the following cases, and then for all cases up to `n`, starting from 0 or 1.

Taking this algorithm to increment a number:

```rust
fn increment(x: u32) -> u32 {
    if x == 0 { return 1; }
    match x % 2 == 1 {
        true => 2 * increment((x + 1) / 2),
        false => x + 1
    }
}
```

We can find out that it is true, for 0, for any even number, it is true (just increment it) and for any odd number, say 5, we want to double one more than its half.

## Modeling the Problem

Some ways of arranging data include:

- Permutations, orderings of a set
- Subsets, selections from a set
- Trees, hierarchical relations between items
- Graphs, relationships between arbitrary pairs of objects
- Points, locations in geometric spaces
- Polygons, borders of groups of geometric spaces
- Strings, sequences of characters, or patterns

All of these are defined recursively.

- Permutations: delete the first element of `n` things and you have `n - 1` things.
- Subsets: Every subset of `n` items contains a subset of `n - 1` items.
- Trees: Delete the root to get two trees, delete a leaf and get a smaller tree.
- Graphs: delete a vertex to get a smaller graph, delete a bridge to get two graphs.
- Points: take arbitrary points and separate them into two groups by drawing a line.
- Polygons: any internal chord cuts it into two smaller polygons.
- Strings: Delete a character from a string.

## Proof by Contradiction

Another way to prove something is through contradiction.

Assume the hypothesis you want to prove is false:
Develop some consequences of the assumption.
Show that the consequence is demonstrably false, showing the assumption is incorrect and the hypothesis is true.

For example, there must be an infinite amount of prime numbers. If this was not the case, there would be a countable amount of them. We would then be able to take their product, and then add one to it. That number would have to be prime, because it would have no non-trivial factors, and thus also be prime. We could repeat this forever, so there must be infinite prime factors.

## Exercises

1. Show that $a + b$ can be less than $min(a, b)$:

If `a` and `b` are both negative.

2. Show that $a * b$ can be less than $min(a, b)$:

If either of `a` and `b` are negative and the other is positive.


Next: [algorithm-analysis](algorithm-analysis.md)
