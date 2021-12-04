import unittest

from typing import List


class Solution(unittest.TestCase):
    def two_sum(self, nums: List[int], target: int) -> List[int]:
        dt = {}
        for (index, value) in enumerate(nums):
            if value in dt:
                return [dt[value], index]
            else:
                dt[target - value] = index

        return [-1, -1]

    def test_1(self):
        self.assertEqual(self.two_sum([2, 7, 11, 15], 9), [0, 1])

    def test_2(self):
        self.assertEqual(self.two_sum([3, 2, 4], 6), [1, 2])

    def test_3(self):
        self.assertEqual(self.two_sum([3, 3], 6), [0, 1])

    def test_4(self):
        self.assertEqual(self.two_sum([], 2), [-1, -1])


if __name__ == '__main__':
    unittest.main()
