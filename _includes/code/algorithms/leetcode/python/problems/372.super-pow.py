#
# @lc app=leetcode id=372 lang=python3
#
# [372] Super Pow
#
# https://leetcode.com/problems/super-pow/description/
#
# algorithms
# Medium (36.45%)
# Total Accepted:    37.8K
# Total Submissions: 103.5K
# Testcase Example:  '2\n[3]'
#
# Your task is to calculate a^b mod 1337 where a is a positive integer and b is
# an extremely large positive integer given in the form of an array.
# 
# 
# Example 1:
# Input: a = 2, b = [3]
# Output: 8
# Example 2:
# Input: a = 2, b = [1,0]
# Output: 1024
# Example 3:
# Input: a = 1, b = [4,3,3,8,5,2]
# Output: 1
# Example 4:
# Input: a = 2147483647, b = [2,0,0]
# Output: 1198
# 
# 
# Constraints:
# 
# 
# 1 <= a <= 2^31 - 1
# 1 <= b.length <= 2000
# 0 <= b[i] <= 9
# b doesn't contain leading zeros.
# 
# 
#
class Solution:
    def superPow(self, a: int, b: List[int]) -> int:
        
