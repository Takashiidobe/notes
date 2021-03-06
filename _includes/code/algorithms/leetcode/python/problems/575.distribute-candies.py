#
# @lc app=leetcode id=575 lang=python3
#
# [575] Distribute Candies
#
# https://leetcode.com/problems/distribute-candies/description/
#
# algorithms
# Easy (61.50%)
# Total Accepted:    110.7K
# Total Submissions: 179.8K
# Testcase Example:  '[1,1,2,2,3,3]'
#
# Alice has n candies, where the i^th candy is of type candyType[i]. Alice
# noticed that she started to gain weight, that is why she visited a doctor.
# 
# The doctor advised Alice to only eat n / 2 of the candies she has (n is
# always even). Alice likes her candies very much. She wants to eat the maximum
# number of different types of candies.
# 
# Given the integer array candyType of length n, return the maximum number of
# different types of candies she can eat, achieving the doctor's advice.
# 
# 
# 
# 
# 
# Example 1:
# 
# 
# Input: candyType = [1,1,2,2,3,3]
# Output: 3
# Explanation: Alice should eat only 3 candies, she currently has 2 candies of
# the first type, 2 candies of the second type, and 2 candies of the third
# type.
# Alice will choose to eat 1 candy of each type. This leads her to eat 3
# different types of candies and we return 3.
# 
# 
# Example 2:
# 
# 
# Input: candyType = [1,1,2,3]
# Output: 2
# Explanation: Alice can eat 2 candies, and she always has the option to eat
# them different [1,2], [1,3], or [2,3].
# 
# 
# Example 3:
# 
# 
# Input: candyType = [6,6,6,6]
# Output: 1
# Explanation: Alice has only one type of candies, she will eat only one type
# i.e., type 6.
# 
# 
# 
# 
# Constraints:
# 
# 
# n == candyType.length
# 2 <= n <= 10^4
# n is even.
# -10^5 <= candyType[i] <= 10^5
# 
# 
#
class Solution:
    def distributeCandies(self, candyType: List[int]) -> int:
        
