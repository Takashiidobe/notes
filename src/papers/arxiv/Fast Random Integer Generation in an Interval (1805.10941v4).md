---
paper id: 1805.10941v4
title: "Fast Random Integer Generation in an Interval"
authors: Daniel Lemire
publication date: 2018-05-28T14:28:04Z
abstract: "In simulations, probabilistic algorithms and statistical tests, we often generate random integers in an interval (e.g., [0,s)). For example, random integers in an interval are essential to the Fisher-Yates random shuffle. Consequently, popular languages like Java, Python, C++, Swift and Go include ranged random integer generation functions as part of their runtime libraries.   Pseudo-random values are usually generated in words of a fixed number of bits (e.g., 32 bits, 64 bits) using algorithms such as a linear congruential generator. We need functions to convert such random words to random integers in an interval ([0,s)) without introducing statistical biases. The standard functions in programming languages such as Java involve integer divisions. Unfortunately, division instructions are relatively expensive. We review an unbiased function to generate ranged integers from a source of random words that avoids integer divisions with high probability. To establish the practical usefulness of the approach, we show that this algorithm can multiply the speed of unbiased random shuffling on x64 processors. Our proposed approach has been adopted by the Go language for its implementation of the shuffle function."
comments: "to appear in ACM Transactions on Modeling and Computer Simulation"
pdf: "[[papers/arxiv/Fast Random Integer Generation in an Interval (1805.10941v4).pdf]]"
url: https://arxiv.org/abs/1805.10941v4
tags: []
---
