# Permutations

Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.

Example 1:

```
Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
```

Example 2:

```
Input: nums = [0,1]
Output: [[0,1],[1,0]]
```

Example 3:

```
Input: nums = [1]
Output: [[1]]
```

## Solution

For permutations, take one item from the set of choices, and then add it
to your running set. You have to do this once for each set, and then
continue recursing until the set of choices is empty.

```python
class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        n = len(nums)
        res = []

        def recurse(nums, choice=[]):
            if len(choice) == n:
                res.append(choice)
            for index, num in enumerate(nums):
                nums.pop(index)
                recurse(nums, choice + [num])
                nums.insert(index, num)
        recurse(nums)

        return res
```
