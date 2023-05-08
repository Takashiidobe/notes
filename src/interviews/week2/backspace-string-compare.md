# Backspace String Compare

Given two strings s and t, return true if they are equal when both are typed into empty text editors. '#' means a backspace character.

Note that after backspacing an empty text, the text will continue empty.

Example 1:

```
Input: s = "ab#c", t = "ad#c"
Output: true
Explanation: Both s and t become "ac".
```

Example 2:

```
Input: s = "ab##", t = "c#d#"
Output: true
Explanation: Both s and t become "".
```

Example 3:

```
Input: s = "a#c", t = "b"
Output: false
Explanation: s becomes "c" while t becomes "b".
```

Constraints:

    1 <= s.length, t.length <= 200
    s and t only contain lowercase letters and '#' characters.

Follow up: Can you solve it in O(n) time and O(1) space?

## Solution

If we iterate through the string in reverse, we know that when we
iterate through the string, if we encounter a character, we can return
it. If we have encountered a `#`, then we can skip the next character.
If we encounter another `#`, we skip the next possible character.

We can do that for both strings and check if they are equal.

```python
class Solution:
    def backspaceCompare(self, s: str, t: str) -> bool:
        def F(S):
            skip = 0
            for x in reversed(S):
                if x == '#':
                    skip += 1
                elif skip:
                    skip -= 1
                else:
                    yield x

        return all(x == y for x, y in itertools.zip_longest(F(s), F(t)))
```
