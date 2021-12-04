---
title: _template
---

balanced Tree\"

## Problem

Given the root of a binary tree, return whether its height is balanced.
That is, for every node in the tree, the absolute difference of the
height of its left subtree and the height of its right subtree is 0 or

1.

## Explanation

Recursively iterate through the tree. When we have a null node, we know
we\'ve gone too far, so return 0. Otherwise, the sum of the tree is
represented by the current value + the sum of the left and right
subtrees.

## Solution

```py
class Solution:
    def solve(self, root):
        if not root:
            return 0
        return root.val + self.solve(root.left) + self.solve(root.right)
```
