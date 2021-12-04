#
# @lc app=leetcode id=1512 lang=python3
#
# [1512] Number of Good Pairs
#
# https://leetcode.com/problems/number-of-good-pairs/description/
#
# algorithms
# Easy (88.17%)
# Total Accepted:    93.3K
# Total Submissions: 106K
# Testcase Example:  '[1,2,3,1,1,3]'
#
# Given an array of integers nums.
#
# A pair (i,j) is called good if nums[i] == nums[j] and i < j.
#
# Return the number of good pairs.
#
#
# Example 1:
#
#
# Input: nums = [1,2,3,1,1,3]
# Output: 4
# Explanation: There are 4 good pairs (0,3), (0,4), (3,4), (2,5) 0-indexed.
#
#
# Example 2:
#
#
# Input: nums = [1,1,1,1]
# Output: 6
# Explanation: Each pair in the array are good.
#
#
# Example 3:
#
#
# Input: nums = [1,2,3]
# Output: 0
#
#
#
# Constraints:
#
#
# 1 <= nums.length <= 100
# 1 <= nums[i] <= 100
#
#
from collections import Counter

"""
n choose 2 can be calculated by n * (n-1) // 2
So in this case we can do that for every set of pairs we encounter.
Assume the case [1,1,3,1,2,3]:
Our Counter() looks like this:
{
    1: 3,
    2: 1,
    3: 2
}
We iterate through the values, and do n choose 2.
there is one triplet, which has 3 pairs (1, 2), (2, 3), (1, 3)
and one pair which has one pair (1, 2)
The answer to that would be 2, which can be found with n (n - 1) // 2.
"""


class Solution:
    def numIdenticalPairs(self, nums: List[int]) -> int:
        counter = Counter(nums)

        pairs = 0
        for num in counter.values():
            pairs += (num * (num - 1) // 2)

        return pairs
