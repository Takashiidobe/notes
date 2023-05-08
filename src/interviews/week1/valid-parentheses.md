# Valid Parentheses

Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

```
Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
```

Example 1:

```
Input: s = "()"
Output: true
```

Example 2:

```
Input: s = "()[]{}"
Output: true
```

Example 3:

```
Input: s = "(]"
Output: false
```

Constraints:

```
1 <= s.length <= 104
s consists of parentheses only '()[]{}'.
```

## Solution

Build a stack of the open parentheses. If you encounter an open
parentheses, add it to the end of the list. If you encounter a closing
parentheses, check if the top of the stack is the same. If it is not,
then we know we have an unbalanced stack, otherwise, keep iterating
through the stack.

At the end, if the stack is empty, we've done a valid traversal.

```python
class Solution:
    def isValid(self, s: str) -> bool:
        stack = []
        dt = { '}': '{', ']': '[', ')': '('}
        for c in s:
            if c in dt.values():
                stack.append(c)
            elif not stack or stack.pop() != dt[c]:
                return False
        return not stack
```
