# Combination Sum

Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.

The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.

It is guaranteed that the number of unique combinations that sum up to target is less than 150 combinations for the given input.

Example 1:

```
Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation:
2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
7 is a candidate, and 7 = 7.
These are the only two combinations.
```

Example 2:

```
Input: candidates = [2,3,5], target = 8
Output: [[2,2,2,2],[2,3,3],[3,5]]
```

Example 3:

```
Input: candidates = [2], target = 1
Output: []
```

## Solution

To solve this problem, we note the following:

1. We must return a set of paths where the candidates sum to target
2. We may use each candidate multiple times
3. Only return unique combinations

So,
1. we can for loop over the candidates to return *unique combinations*
2. We have two choices, either take the current candidate or skip it, to
   allow *using each candidate as many times as possible*
3. Keep a list and copy it to a result array when candidates sum to
   target.

```python
class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        ans = []
        n = len(candidates)
        def dfs(i, remaining, curr):
            if remaining == 0:
                ans.append(curr.copy())
                return
            if remaining < 0 or i >= n:
                return
            candidate = candidates[i]
            curr.append(candidate)
            dfs(i, remaining - candidate, curr)
            curr.pop()
            dfs(i + 1, remaining, curr)

        dfs(0, target, [])

        return ans
```
