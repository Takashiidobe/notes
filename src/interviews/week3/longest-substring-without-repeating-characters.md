# Longest Substring Without Repeating Characters

Given a string s, find the length of the longest substring without repeating characters.

Example 1:

```
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
```

Example 2:

```
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
```

Example 3:

```
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
```

## Solution

We generate a set of characters to be able to query the existing
characters in O(1) time.

We then generate a sliding window that we widen every time we see a new
unique character.

When we see a non-unique character, we shorten the sequence until we see
the same character, and then continue from there.

```python
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        max_so_far, l, r = 0, 0, 0
        character_set = set()
        str_len = len(s)

        while r < str_len:
            right_char = s[r]
            if right_char in character_set:
                while l <= r:
                    left_char = s[l]
                    character_set.remove(left_char)
                    l += 1
                    if left_char == right_char:
                        break
            character_set.add(right_char)
            r += 1
            max_so_far = max(max_so_far, r - l)
        return max_so_far
```
