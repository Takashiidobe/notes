# Print Binary Tree

Given the root of a binary tree, construct a 0-indexed m x n string matrix res that represents a formatted layout of the tree. The formatted layout matrix should be constructed using the following rules:

- The height of the tree is height and the number of rows m should be equal to height + 1.
- The number of columns n should be equal to 2height+1 - 1.
- Place the root node in the middle of the top row (more formally, at location `res[0][(n-1)/2]`).
- For each node that has been placed in the matrix at position `res[r][c]`, place its left child at `res[r+1][c-2^height-r-1]` and its right child at `res[r+1][c+2^height-r-1]`.
- Continue this process until all the nodes in the tree have been placed.
- Any empty cells should contain the empty string "".

Return the constructed matrix res.

## Approach

To print the binary tree, we need coordinates that can hold all of the
children at the leaf level. To do so, we need to first find the height
of the binary tree.

```python
def depth(node, level):
    if not node:
        return level
    return max(
        depth(node.left, level + 1),
        depth(node.right, level + 1),
    )

height = depth(root, 0)
```

That would return a height of 0 if there is no tree, or 1 if there's
just a root, etc.

With the height, we can calculate the width of each row in our result.

To figure it out, listing out the height -> max width should help:

1 -> 1
2 -> 3
3 -> 7
4 -> 15
...

The formula for this is (2 ^ height - 1).

So that's the width of each array.

```python
width = 2 ** height - 1
```

Finally, to create the array itself:

```python
arr = [[''] * width for _ in range(height)]
```

Next, we need to re-traverse the tree and keep track of where to put
each item in the array.

The root should go in the middle of the width.
Its left child should go between (0..mid)
Its right child should go between (mid + 1..width)

We don't include mid because this is where we've placed our root node.

Thus, in our recursion, we want to pass in the left and right bounds and
choose the middle of that.

```python
def traverse(node, level, left, right):
    if not node:
        return
    mid = (left + right) // 2
    arr[level][mid] = str(node.val)
    traverse(node.left, level + 1, left, mid - 1)
    traverse(node.right, level + 1, mid + 1, right)

traverse(root, 0, 0, width - 1) 
```
