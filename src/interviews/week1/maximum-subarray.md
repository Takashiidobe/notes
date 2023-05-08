# Maximum Subarray

Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

A subarray is a contiguous part of an array.

Example 1:

```
Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.
```

Example 2:

```
Input: nums = [1]
Output: 1
```

Example 3:

```
Input: nums = [5,4,-1,7,8]
Output: 23
```

## Solution

Since we must take at least one number, take the first number, and
record it as our start.

For every number afterwards, we have two choices:

We either can take the current number if the running sum before it is as
least as big (otherwise, we would do better to just start here).

Finally, we tally the total maximum, which we return.

```python
class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        curr, total_max = nums[0], nums[0]

        for num in nums[1:]:
            curr += num
            curr = max(curr, num)
            total_max = max(total_max, curr)

        return total_max
```
