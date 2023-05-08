# Morris Traversal

How do you free memory in a free-list without hitting an OOM error?

Let's say we have a binary tree that is unbalanced and call a destructor
on each node. Well, to call a destructor on each node, we need to call
the destructor on its child nodes... In a balanced tree, this requires
O(log n) memory, so this isn't so expensive. But in a linked list, this
would require O(n) memory, and likely smash the stack.

How would we do better?

We can actually traverse a tree in O(1) space while visiting each node
up to four times.

```python 
def inorderTraversal(self, root: TreeNode) -> List[int]:
    if not root:
        return []
    
    result = []
    
    while root:
        if root.left:  
            node = root.left
            
            while node.right and node.right!=root:  
                node = node.right
                
            if not node.right:   
                node.right = root
                root = root.left  
            else: 
                result.append(root.val)
                root = root.right
            
        else: 
            result.append(root.val)
            root = root.right
            
    return result
```
