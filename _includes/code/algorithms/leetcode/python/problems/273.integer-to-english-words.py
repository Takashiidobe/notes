#
# @lc app=leetcode id=273 lang=python3
#
# [273] Integer to English Words
#
# https://leetcode.com/problems/integer-to-english-words/description/
#
# algorithms
# Hard (27.46%)
# Total Accepted:    202.8K
# Total Submissions: 733.3K
# Testcase Example:  '123'
#
# Convert a non-negative integer num to its English words representation.
# 
# 
# Example 1:
# Input: num = 123
# Output: "One Hundred Twenty Three"
# Example 2:
# Input: num = 12345
# Output: "Twelve Thousand Three Hundred Forty Five"
# Example 3:
# Input: num = 1234567
# Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty
# Seven"
# Example 4:
# Input: num = 1234567891
# Output: "One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven
# Thousand Eight Hundred Ninety One"
# 
# 
# Constraints:
# 
# 
# 0 <= num <= 2^31 - 1
# 
# 
#
class Solution:
    def numberToWords(self, num: int) -> str:
        
