#
# @lc app=leetcode id=58 lang=python3
#
# [58] Length of Last Word
#
# https://leetcode.com/problems/length-of-last-word/description/
#
# algorithms
# Easy (33.27%)
# Total Accepted:    446.4K
# Total Submissions: 1.3M
# Testcase Example:  '"Hello World"'
#
# Given a string s consists of some words separated by spaces, return the
# length of the last word in the string. If the last word does not exist,
# return 0.
# 
# A word is a maximal substring consisting of non-space characters only.
# 
# 
# Example 1:
# Input: s = "Hello World"
# Output: 5
# Example 2:
# Input: s = " "
# Output: 0
# 
# 
# Constraints:
# 
# 
# 1 <= s.length <= 10^4
# s consists of only English letters and spaces ' '.
# 
# 
#
class Solution:
    def lengthOfLastWord(self, s: str) -> int:
        
