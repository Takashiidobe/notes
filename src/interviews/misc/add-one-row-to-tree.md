# Add One Row to Tree

Given the root of a binary tree and two integers val and depth, add a row of nodes with value val at the given depth depth.

Note that the root node is at depth 1.

The adding rule is:

- Given the integer depth, for each not null tree node cur at the depth depth - 1, create two tree nodes with value val as cur's left subtree root and right subtree root.
- cur's original left subtree should be the left subtree of the new left subtree root.
- cur's original right subtree should be the right subtree of the new right subtree root.
- If depth == 1 that means there is no depth depth - 1 at all, then create a tree node with value val as the new root of the whole original tree, and the original tree is the new root's left subtree.

## Approach

For this problem, there are two cases to handle, when depth == 1 and
otherwise.

When depth == 1, as the problems states, we create a new node with val,
and set its left subtree to the tree.

```python
def addOneRow(root: Optional[TreeNode], val: int, depth: int) -> Optional[TreeNode]:
    if depth == 1:
        new_node = TreeNode(val, root, None)
        return new_node
```

For all other cases, we want to keep track of the depth and when we hit
depth - 1, we want to implement the logic of the problem:

1. create a new left node that has a subtree of the current left subtree
2. create a new right node that has a subtree of the current right subtree
3. and then attach these to the current node.

Finally, we can return here because we don't need to process the rest of
the tree.

```python
def traverse(node, curr_depth, parent):
    if not node:
        return
    if curr_depth == depth - 1:
         new_left = TreeNode(val, node.left, None) 
         new_right = TreeNode(val, None, node.right) 
         node.left = new_left
         node.right = new_right
         return
         
    traverse(node.left, curr_depth + 1, node)
    traverse(node.right, curr_depth + 1, node)
```
