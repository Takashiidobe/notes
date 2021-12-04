---
title: "867 Count Nodes in Complete Binary Tree"
---

## Problem

Given a complete binary tree root, return the number of nodes in the
tree.

This should be done in O(log n)\^2

## Explanation

We start with the root node, as level 1. We create two pointers, one
called left and one called right. The left pointer only goes left, and
the right pointer only goes to the right child. Each time there is a
left and right child, increment the level by one.

There are two ways this algorithm terminates: Either both the left and
right child are none (in which case this tree is a full binary tree, so
the number of nodes is (2 \^ level - 1) or the left child exists, but
the right child doesn\'t. In this case, we can manually count the number
of nodes in the last level of the tree, and sum it with the count of the
previous level.

## Solution

### Naive, Counting all nodes

```py
class Solution:
    def solve(self, root):
        if not root:
            return 0
        return 1 + self.solve(root.left) + self.solve(root.right)
```
