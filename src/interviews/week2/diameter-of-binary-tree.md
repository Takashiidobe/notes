# Diameter of Binary Tree

Given the root of a binary tree, return the length of the diameter of the tree.

The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.

The length of a path between two nodes is represented by the number of edges between them.

Example 1:

```
Input: root = [1,2,3,4,5]
Output: 3
Explanation: 3 is the length of the path [4,2,1,3] or [5,2,1,3].
```

Example 2:

```
Input: root = [1,2]
Output: 1
```

## Solution

For each node, we want to calculate the maximum path, which is the
longest depth of its left child + right child + 1.

We traverse the tree and keep track of the maximum value for each node.

```python
class Solution:
    def diameterOfBinaryTree(self, root: TreeNode) -> int:
        ans = 0
        def depth(root):
            nonlocal ans
            if not root:
                return 0
            l_depth = depth(root.left)
            r_depth = depth(root.right)
            ans = max(ans, l_depth + r_depth)
            return 1 + max(l_depth, r_depth)

        depth(root)
        return ans
```
