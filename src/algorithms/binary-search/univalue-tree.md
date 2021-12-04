---
title: "251 Univalue Tree"
---

## Problem

Given a binary tree root, return whether all values in the tree are the
same.

## Explanation

We want to make sure to check all values are the same: So, we\'ll create
a function to take care of the edge case, where there is no node. Then,
we\'ll make a helper function that takes the root node and its value. If
the root node doesn\'t exist, this function should return true.
Otherwise, if it doesn\'t equal the val, it returns false. Otherwise, it
should return the combination of its left and right subtrees.

## Solution

```py
class Solution:
    def solve(self, root):
        if not root:
            return True
        return self.helper(root, root.val)

    def helper(self, root, val):
        if not root:
            return True
        if root.val != val:
            return False
        return self.helper(root.left, val) and self.helper(root.right, val)
```
