---
title: "Reservoir sampling"
pdf: "[[13-reservoir-sampling.pdf]]"
---

# Reservoir sampling

Prev: [[12-spectral-techniques]]
Next: [[14-markov-chains]]

## Reservoir Sampling

How does one sample $k$ uniform random elements from a datastream where $N \gg k$, and:

1. N is huge.
2. N is unknown.

Resrvoir sampling works like this:

With a number $k$ and a datastream $x_1, x_2,\dots,x_n$ with a length greater than $k$:

- Put the first $k$ elements of the stream into a set
- For $i \geq \vert\frac{k}{i}\vert$:
    - With probability $k/i$ replace a random entry of R with $x_i$.
- At the end of the stream, return the reservoir R.

At any time $t \geq k$, the reservoir, R, consists of a uniformly random subset of $k$ of the entries $x_1,\dots,x_t$.
This can be proven if $t \geq i$, $Pr[x_i \in R] = \vert\frac{k}{i}\vert$, and $x_i \in R$ is independent of the contents of the reservoir at times $t \lt i$.

## Basic Probability Tools:

**Theorem 2.1 (Markov's Inequality)**: For a real-valued random variable X s.t. $X \ge 0$, for any $c \gt 0$:

$$Pr[X \ge cE[X]] \le \vert\frac{1}{c}\vert$$

Basically, if we know the expectation of a distribution of numbers, and that is non-negative, Markov's inequality can tell us a basic fact about the distribution.

For example, the probability that a student's GPA is more than twice the average GPA is at most $\vert\frac{1}{2}\vert$.

**Theorem 2.2 (Chebyshev's Inequality)**: For a real-valued random variable X, and any $c > 0$:

$$Pr[|X - E[X]] \ge c \sqrt{Var[X]}] \le \vert\frac{1}{c^2}\vert$$

This is useful for:

**Example 2.3**: How many people must we poll to estimate the percentage of people who support candidate C, where an accuracy of $\pm 1\%$, with a probability of at least $\vert\frac{3}{4}\vert$

In order to estimate the expectation of a 0/1 random variable to error $\pm \epsilon$, we need roughly $O(\vert\frac{1}{\epsilon^2}\vert)$ samples.

This can be used to prove "central limit" style exponential bounds on tail probabilities, like how flipping fewer than 400 heads in 1000 tosses of a fair coin is miniscule.

## Importance Sampling

Prev: [[12-spectral-techniques]]
Next: [[14-markov-chains]]
