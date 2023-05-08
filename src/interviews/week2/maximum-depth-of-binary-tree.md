# Maximum Depth of Binary Tree

Given the root of a binary tree, return its maximum depth.

A binary tree's maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

Example 1:

```
Input: root = [3,9,20,null,null,15,7]
Output: 3
```

Example 2:

```
Input: root = [1,null,2]
Output: 2
```

## Solution

To find the maximum depth, we traverse the whole tree, and keep track of
the maximum level we've encountered before. The root starts out at level
1, and any children increment the level by 1.

```python
class Solution:
    def maxDepth(self, root: Optional[TreeNode]) -> int:
        if not root:
            return 0
        q = deque([(root, 1)])

        max_level = 0

        while q:
            node, level = q.popleft()
            max_level = max(max_level, level)
            q.append((node.left, level + 1)) if node.left
            q.append((node.right, level + 1)) if node.right

        return max_level
```
