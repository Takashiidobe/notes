# Invert Binary Tree

Given the root of a binary tree, invert the tree, and return its root.

Example 1:

```
Input: root = [4,2,7,1,3,6,9]
Output: [4,7,2,9,6,3,1]
```

Example 2:

```
Input: root = [2,1,3]
Output: [2,3,1]
```

Example 3:

```
Input: root = []
Output: []
```

## Solution

To invert a binary tree, for the children of each node, we swap its left
and right children.

With BFS:

```python
class Solution:
    def invertTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        q = Deque([root])

        while q:
            node = q.popleft()
            if node:
                node.left, node.right = node.right, node.left
                q.append(node.left)
                q.append(node.right)

        return root
```

With DFS:

```python
class Solution:
    def invertTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        def traverse(node):
            if node:
                node.left, node.right = node.right, node.left
                traverse(node.left)
                traverse(node.right)

        traverse(root)
        return root
```
