# Product of Array Except Self

Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].

The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

You must write an algorithm that runs in O(n) time and without using the division operation.

Example 1:

```
Input: nums = [1,2,3,4]
Output: [24,12,8,6]
```

Example 2:

```
Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]
```

Constraints:

    2 <= nums.length <= 105
    -30 <= nums[i] <= 30
    The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

## Solution

Iterate through the array with two pointers, where we multiply the left
side by the left pointer, and the right side by the right pointer.

```python
class Solution:
    def productExceptSelf(self, nums):
        res = [1] * len(nums)
        lprod = 1
        rprod = 1
        for i, num in enumerate(nums):
            res[i] *= lprod
            lprod *= num
            res[~i] *= rprod
            rprod *= nums[~i]
        return res
```
