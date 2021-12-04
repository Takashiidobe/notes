#
# @lc app=leetcode id=172 lang=python3
#
# [172] Factorial Trailing Zeroes
#
# https://leetcode.com/problems/factorial-trailing-zeroes/description/
#
# algorithms
# Easy (37.97%)
# Total Accepted:    231.9K
# Total Submissions: 608.7K
# Testcase Example:  '3'
#
# Given an integer n, return the number of trailing zeroes in n!.
# 
# Follow up: Could you write a solution that works in logarithmic time
# complexity?
# 
# 
# Example 1:
# 
# 
# Input: n = 3
# Output: 0
# Explanation: 3! = 6, no trailing zero.
# 
# 
# Example 2:
# 
# 
# Input: n = 5
# Output: 1
# Explanation: 5! = 120, one trailing zero.
# 
# 
# Example 3:
# 
# 
# Input: n = 0
# Output: 0
# 
# 
# 
# Constraints:
# 
# 
# 1 <= n <= 10^4
# 
# 
#
class Solution:
    def trailingZeroes(self, n: int) -> int:
        
