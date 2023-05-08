# Binary Tree Level Order Traversal

Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level).

Example 1:

```
Input: root = [3,9,20,null,null,15,7]
Output: [[3],[9,20],[15,7]]
```

Example 2:

```
Input: root = [1]
Output: [[1]]
```

Example 3:

```
Input: root = []
Output: []
```

## Solution

This solution is easiest with a bfs, where one node is traversed to the
end.

```python
class Solution:
    def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        if not root:
            return []

        # process the left nodes of the tree first, then the right
        q = Deque([(root, 0)])

        res = []

        while q:
            node, level = q.popleft()
            if len(res) <= level:
                res.append([node.val])
            else:
                res[level].append(node.val)
            if node.left:
                q.append((node.left, level + 1))
            if node.right:
                q.append((node.right, level + 1))

        return res
```
