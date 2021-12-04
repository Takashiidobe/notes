---
title: 132-height-balanced-tree
---

balanced Tree\"

## Problem

Given the root of a binary tree, return whether its height is balanced.
That is, for every node in the tree, the absolute difference of the
height of its left subtree and the height of its right subtree is 0 or

1.

## Explanation

We need to make sure that the absolute difference between both the left
and right side is \<= 1. To do this, write a helper function that
returns the height of the node: when the node is None, it returns zero,
otherwise, it returns the maximum of its left and right height, which is
1 + its height applied to the same function.

For the main function, we call this helper on our current node (root),
by calculating the left and right height, and making sure the absolute
difference is less than or equal to 1. Then, we make sure that this
property applies for all children, by calling our main function on our
left and right children.

## Solution

```py
class Solution:
    def height(self, node):
        if not node:
            return 0
        left_height = 1 + self.height(node.left)
        right_height = 1 + self.height(node.right)
        return max(left_height, right_height)

    def solve(self, root):
        if not root:
            return True
        left_height = self.height(root.left)
        right_height = self.height(root.right)
        is_valid = abs(left_height - right_height) <= 1
        return is_valid and self.solve(root.left) and self.solve(root.right)
```
