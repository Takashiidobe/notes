---
title: 63-tree-sum
---

Sum\"

Given a binary tree `root`, return the sum of all values in the tree.

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
