# Word Break

## Solution

This is an O(n^3) solution requiring tabulation.

```python
class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        wordSet = set(wordDict)
        dp = [1] + [0] * len(s)
        for i in range(1, len(s)+1):
            for j in range(i):
                if dp[j] == 1 and s[j:i] in wordSet:
                    dp[i] = 1
                    break
        return dp[-1] == 1
```
