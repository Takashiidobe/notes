---
title: shortest-path-in-binary-matrix
---

Path in Binary Matrix\"

# Problem

- Find the shortest path in a binary matrix
- You are allowed to move 4-directionally
- 0 means you can pass through, 1 means you cannot pass.

## Code

## Optimizations

- Precalculate if you can reach the end; if you cannot pass through
  vertically or horizontally from start to end, you would reject it.
