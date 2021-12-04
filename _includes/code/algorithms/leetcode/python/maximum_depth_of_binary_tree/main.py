import unittest


class Solution(unittest.TestCase):
    def max_depth(self, root: TreeNode) -> int:
        if not root:
            return 0
        else:
            return max(self.maxDepth(root.left), self.maxDepth(root.right)) + 1

    def test_1(self):
        root = TreeNode(3)
        root.left = TreeNode(20)
        root.right = TreeNode(9)
        root.left.left = TreeNode(15)
        root.left.right = TreeNode(7)
        self.assertEqual(self.max_depth(root), 3)

    def test_2(self):
        self.assertEqual(self.max_depth(None), 0)

    def test_3(self):
        root = TreeNode(1)
        root.left = TreeNode(1)
        root.right = TreeNode(1)
        root.right.right = TreeNode(1)
        root.right.right.right = TreeNode(1)
        self.assertEqual(self.max_depth(root), 4)


if __name__ == '__main__':
    unittest.main()
