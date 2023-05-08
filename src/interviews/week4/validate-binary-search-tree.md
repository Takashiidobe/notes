# Validate Binary Search Tree

Given the root of a binary tree, determine if it is a valid binary search tree (BST).

A valid BST is defined as follows:

```
The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.
```

Example 1:

```
Input: root = [2,1,3]
Output: true
```

Example 2:

```
Input: root = [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.
```

## Solution

To check if a BST is valid, there is one condition:

1. `left < middle < right`.

Thus, we must keep track of the minimum left value and the maximum right
value for each node as we traverse it.

If it is, then the left child must be less than its parent's value,
and the right child must be greater than its parent's value.

```python
class Solution:
    def isValidBST(self, root: Optional[TreeNode]) -> bool:
        def validate(root, left = float('-inf'), right = float('inf')):
            if not root:
                return True
            if left < root.val < right:
                return validate(root.left, left, root.val) and validate(root.right, root.val, right)
            return False
        return validate(root)
```
