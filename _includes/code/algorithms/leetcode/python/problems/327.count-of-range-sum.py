#
# @lc app=leetcode id=327 lang=python3
#
# [327] Count of Range Sum
#
# https://leetcode.com/problems/count-of-range-sum/description/
#
# algorithms
# Hard (35.49%)
# Total Accepted:    46.3K
# Total Submissions: 129.6K
# Testcase Example:  '[-2,5,-1]\n-2\n2'
#
# Given an integer array nums, return the number of range sums that lie in
# [lower, upper] inclusive.
# Range sum S(i, j) is defined as the sum of the elements in nums between
# indices i and j (i ≤ j), inclusive.
# 
# Note:
# A naive algorithm of O(n^2) is trivial. You MUST do better than that.
# 
# Example:
# 
# 
# Input: nums = [-2,5,-1], lower = -2, upper = 2,
# Output: 3 
# Explanation: The three ranges are : [0,0], [2,2], [0,2] and their respective
# sums are: -2, -1, 2.
# 
# 
# Constraints:
# 
# 
# 0 <= nums.length <= 10^4
# 
# 
#
class Solution:
    def countRangeSum(self, nums: List[int], lower: int, upper: int) -> int:
        
