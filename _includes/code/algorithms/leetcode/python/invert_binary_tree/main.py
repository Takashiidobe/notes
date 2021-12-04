import unittest
from tree_node import TreeNode


class Solution(unittest.TestCase):
    def invert_tree(self, root: TreeNode) -> TreeNode:
        if not root:
            return None

        root.left, root.right = root.right, root.left
        self.invert_tree(root.left)
        self.invert_tree(root.right)

        return root

    def test_1(self):
        root = TreeNode(0)
        root.left = TreeNode(3)
        root.right = TreeNode(5)

        ans = TreeNode(0)
        ans.left = TreeNode(5)
        ans.right = TreeNode(3)
        self.assertEqual(self.invert_tree(root), ans)

    def test_2(self):
        self.assertEqual(self.invert_tree(None), None)


if __name__ == '__main__':
    unittest.main()
