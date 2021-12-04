#
# @lc app=leetcode id=1360 lang=python3
#
# [1360] Number of Days Between Two Dates
#
# https://leetcode.com/problems/number-of-days-between-two-dates/description/
#
# algorithms
# Easy (47.59%)
# Total Accepted:    16.2K
# Total Submissions: 34.1K
# Testcase Example:  '"2019-06-29"\n"2019-06-30"'
#
# Write a program to count the number of days between two dates.
# 
# The two dates are given as strings, their format is YYYY-MM-DD as shown in
# the examples.
# 
# 
# Example 1:
# Input: date1 = "2019-06-29", date2 = "2019-06-30"
# Output: 1
# Example 2:
# Input: date1 = "2020-01-15", date2 = "2019-12-31"
# Output: 15
# 
# 
# Constraints:
# 
# 
# The given dates are valid dates between the years 1971 and 2100.
# 
# 
#
class Solution:
    def daysBetweenDates(self, date1: str, date2: str) -> int:
        
