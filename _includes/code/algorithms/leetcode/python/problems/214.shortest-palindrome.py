#
# @lc app=leetcode id=214 lang=python3
#
# [214] Shortest Palindrome
#
# https://leetcode.com/problems/shortest-palindrome/description/
#
# algorithms
# Hard (30.12%)
# Total Accepted:    106.4K
# Total Submissions: 351.3K
# Testcase Example:  '"aacecaaa"'
#
# Given a string s, you can convert it to a palindrome by adding characters in
# front of it. Find and return the shortest palindrome you can find by
# performing this transformation.
# 
# 
# Example 1:
# Input: s = "aacecaaa"
# Output: "aaacecaaa"
# Example 2:
# Input: s = "abcd"
# Output: "dcbabcd"
# 
# 
# Constraints:
# 
# 
# 0 <= s.length <= 5 * 10^4
# s consists of lowercase English letters only.
# 
# 
#
class Solution:
    def shortestPalindrome(self, s: str) -> str:
        
