#
# @lc app=leetcode id=1081 lang=python3
#
# [1081] Smallest Subsequence of Distinct Characters
#
# https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/description/
#
# algorithms
# Medium (53.19%)
# Total Accepted:    17.1K
# Total Submissions: 32.1K
# Testcase Example:  '"bcabc"'
#
# Return the lexicographically smallest subsequence of s that contains all the
# distinct characters of s exactly once.
# 
# Note: This question is the same as 316:
# https://leetcode.com/problems/remove-duplicate-letters/
# 
# 
# Example 1:
# 
# 
# Input: s = "bcabc"
# Output: "abc"
# 
# 
# Example 2:
# 
# 
# Input: s = "cbacdcbc"
# Output: "acdb"
# 
# 
# 
# Constraints:
# 
# 
# 1 <= s.length <= 1000
# s consists of lowercase English letters.
# 
# 
#
class Solution:
    def smallestSubsequence(self, s: str) -> str:
        
