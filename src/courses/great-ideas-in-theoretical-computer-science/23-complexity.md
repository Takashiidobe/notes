---
title: "Complexity"
---

# Complexity

Prev: [[22-23-quantum-algorithms]]

## Motivating Complexity Theory

Penrose says that it's impossible for a computer to simulate the human brain. His argument is based on Godel's Incompleteness Theorem: for any system $F$, we can construct a Godel sentence $G(F)$ that the computer cannot prove, but a human can prove.

Prof Aaronson proposes that you could have some lookup table that stores the result of an "intelligent" human response to some input, and return it. Of course, this table would have to be incredibly large, but it wouldn't be impossible to create.

### Dijkstra's Algorithm

Dijkstra created an algorithm that finds the shortest path between two veritices of a graph, in a time linear to the amount of edges. Clearly this is computable, but an algorithm that does it efficiently is much better.

## Circuit Complexity

Given a Boolean function $f : \{0, 1\}^n \to \{0, 1\}$, what is the size of the smallest circuit that computes it?

Trying to calculate the XOR of $n$ input bits, $x_1,\dots,x_n$, we need $n - 1$ gates. You can XOR $x_1$ with $x_2$, and $x_3$, all the way up to $n - 1$.

### Shannon's Counting Argument

Is there a boolean function with $n$ inputs that requires a circuit of exponential size in $n$?

Shannon made an argument for why such a function must exist (without giving an exmaple, which is called *non-constructive*):

Each boolean function with $n$ inputs is a truth table with $2^n$ entries, and each entry can be 0 or 1. This leads to $2^{2^n}$ functions.

There are $n$ inputs and $T$ gates. Therefore, there are no more than $(n + T)^{2T})$ circuits available. Every circuit can compute only one Boolean function. Thus, to represent all $2^{2^n}$, we require $(n + T)^{2T} \ge 2^{2^n}$. Taking the log of both sides, $T$ is $\frac{2^n}{2n}$. Thus, there must be a boolean function with exponential complexity.

## Hartmanis-Stearns

Hartmanis and Stearns proved how to construct problems that can take any desired number of steps for a Turing machine to solve.

Let's say we want to create an algorithm that terminates in $n^3$ steps.

**Claim**: Any turing machine requires at least $n^3$ steps to solve it.
**Proof**: Suppose there was a machine, P, that solved the problem in $n^2.99$ steps. Modify P to produce a machine, P', which acts as follows given a Turing machine $M$ and input $n$:

1. Runs forever if $M$ halts in at most $n^3$ steps given its own code as input.
2. Halts if $M$ runs for more than $n^3$ steps given its own code as input.

P' halts in at most $n^2.99$ steps, which is fewer than $n^3$ steps.

Now run $P'(P', n)$. If P' halts, then it runs forever (case 1). If P' runs forever, it will halt (case 2).

Thus, P could not have existed in the first place.

Prev: [[22-23-quantum-algorithms]]
