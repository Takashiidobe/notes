# Balanced Binary Tree

Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as:

    a binary tree in which the left and right subtrees of every node differ in height by no more than 1.

Example 1:

```
Input: root = [3,9,20,null,null,15,7]
Output: true
```

Example 2:

```
Input: root = [1,2,2,3,3,null,null,4,4]
Output: false
```

Example 3:

```
Input: root = []
Output: true
```

## Solution

When traversing the tree, we want to keep track of two things:

1. Current height.
2. If the node is height balanced.

Every node's left child and right child should be balanced, and itself
should be balanced (`left_height - right_height <= 1`), and the current
node's height should be the maximum of the right and left subtrees.

```python
class Solution:
    def isBalanced(self, root: Optional[TreeNode]) -> bool:
        def get_height(node, height = 0):
            if not node:
                return (height, True)

            left_height, left_balanced = get_height(node.left, height + 1)
            right_height, right_balanced = get_height(node.right, height + 1)
            max_height = max(left_height, right_height)
            is_balanced = abs(left_height - right_height) <= 1
            return (max_height, is_balanced and left_balanced and right_balanced)

        return get_height(root)[1]
```
