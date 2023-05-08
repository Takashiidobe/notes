# 3Sum

Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

Example 1:

```
Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation:
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not matter.
```

Example 2:

```
Input: nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.
```

Example 3:

```
Input: nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0.
```

## Solution

Sort the array, and then iterate through the array -- for every
iteration, have three pointers, where you fix a number, and then select
a number smaller and larger than it. For each iteration, you can binary
search for a better possibility that matches.

```python
class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        res = []
        n = len(nums)
        nums = sorted(nums)
        for i in range(n-2):
            if i > 0 and nums[i] == nums[i-1]:
                continue
            j = i+1
            k = n-1
            new_target = -nums[i]
            while j < k:
                summ = nums[j] + nums[k]
                if summ < new_target:
                    j += 1
                elif summ > new_target:
                    k -= 1
                else:
                    res.append([nums[i], nums[j], nums[k]])
                    while j < k and nums[j+1] == nums[j]:
                        j += 1
                    j += 1
                    while k > j and nums[k-1] == nums[k]:
                        k -= 1
                    k -= 1
        return res
```
