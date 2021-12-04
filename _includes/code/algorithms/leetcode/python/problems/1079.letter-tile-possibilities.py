#
# @lc app=leetcode id=1079 lang=python3
#
# [1079] Letter Tile Possibilities
#
# https://leetcode.com/problems/letter-tile-possibilities/description/
#
# algorithms
# Medium (75.52%)
# Total Accepted:    39.7K
# Total Submissions: 52.6K
# Testcase Example:  '"AAB"'
#
# You have n  tiles, where each tile has one letter tiles[i] printed on it.
# 
# Return the number of possible non-empty sequences of letters you can make
# using the letters printed on those tiles.
# 
# 
# Example 1:
# 
# 
# Input: tiles = "AAB"
# Output: 8
# Explanation: The possible sequences are "A", "B", "AA", "AB", "BA", "AAB",
# "ABA", "BAA".
# 
# 
# Example 2:
# 
# 
# Input: tiles = "AAABBC"
# Output: 188
# 
# 
# Example 3:
# 
# 
# Input: tiles = "V"
# Output: 1
# 
# 
# 
# Constraints:
# 
# 
# 1 <= tiles.length <= 7
# tiles consists of uppercase English letters.
# 
# 
#
class Solution:
    def numTilePossibilities(self, tiles: str) -> int:
        
