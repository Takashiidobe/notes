#
# @lc app=leetcode id=434 lang=python3
#
# [434] Number of Segments in a String
#
# https://leetcode.com/problems/number-of-segments-in-a-string/description/
#
# algorithms
# Easy (37.77%)
# Total Accepted:    83.9K
# Total Submissions: 222.2K
# Testcase Example:  '"Hello, my name is John"'
#
# You are given a string s, return the number of segments in the string. 
# 
# A segment is defined to be a contiguous sequence of non-space characters.
# 
# 
# Example 1:
# 
# 
# Input: s = "Hello, my name is John"
# Output: 5
# Explanation: The five segments are ["Hello,", "my", "name", "is", "John"]
# 
# 
# Example 2:
# 
# 
# Input: s = "Hello"
# Output: 1
# 
# 
# Example 3:
# 
# 
# Input: s = "love live! mu'sic forever"
# Output: 4
# 
# 
# Example 4:
# 
# 
# Input: s = ""
# Output: 0
# 
# 
# 
# Constraints:
# 
# 
# 0 <= s.length <= 300
# s consists of lower-case and upper-case English letters, digits or one of the
# following characters "!@#$%^&*()_+-=',.:".
# The only space character in s is ' '.
# 
# 
#
class Solution:
    def countSegments(self, s: str) -> int:
        
