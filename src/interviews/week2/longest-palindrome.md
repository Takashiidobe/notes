# Longest Palindrome

Given a string s which consists of lowercase or uppercase letters, return the length of the longest palindrome that can be built with those letters.

Letters are case sensitive, for example, "Aa" is not considered a palindrome here.

Example 1:

```
Input: s = "abccccdd"
Output: 7
Explanation: One longest palindrome that can be built is "dccaccd", whose length is 7.
```

Example 2:

```
Input: s = "a"
Output: 1
Explanation: The longest palindrome that can be built is "a", whose length is 1.
```

## Solution

We want to greedily take as many characters from each set of letters as
we can. To do so, we do the following:

1. If we encounter an odd number and we've never encountered an odd
   number before, we take it (for our center).
2. If we encounter an even number, we take it.
3. If we encounter an odd number, but we've encountered an odd number
   before, we take the number - 1. (since we can only have one unique
   center).

This maximizes the length of a potential palindrome.

```python
class Solution:
    def longestPalindrome(self, s: str) -> int:
        ans = 0
        for v in collections.Counter(s).values():
            ans += v // 2 * 2
            if ans % 2 == 0 and v % 2 == 1:
                ans += 1
        return ans
```
