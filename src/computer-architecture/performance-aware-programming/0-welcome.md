---
title: 0-welcome
date created: Saturday, March 1st 2025, 8:32:23 pm
date modified: Saturday, March 1st 2025, 9:04:42 pm
---

- Performance aware programming is not "optimization"
- Optimization refers to taking an already written program and trying to maximize its performance.
- Performance Aware Programming (PAP) is meant to take a higher level view and find the inefficiencies from first principles
- There are programs that are 1000x slower than they should be.

- People think there are two ways to optimize a program:
1. Reduce the number of instructions
2. Increase the speed instructions move through the CPU

Modern CPUs are very complicated; they process instructions in parallel, execute instructions out of order, have complicated caching to reduce the cost of loads, and have different areas to do things in parallel (FP registers, SIMD registers)

Computers starting in about the 90s became too complicated to keep in your head, and counting cycles became much harder. But there's still a method to the madness

