# Majority Element

Given an array nums of size n, return the majority element.

The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.

Example 1:

```
Input: nums = [3,2,3]
Output: 3
```

Example 2:

```
Input: nums = [2,2,1,1,1,2,2]
Output: 2
```

## Solution

To find the majority element, we can iterate through the array, keeping
track of the current element and the count of its numbers.

If we encounter the same number, increment the count. Otherwise,
decrement the count. If the count becomes 0, then the new candidate
becomes the current number.

Since we can guarantee there is a majority element, there is only one
pass required. If not, we could pass through again and make sure that
the majority element is actually correct.

```python
class Solution:
    def majorityElement(self, nums: List[int]) -> int:
        count = 1
        curr = nums[0]

        for num in nums[1:]:
            count += (1 if curr == num else -1)
            if count == 0:
                curr = num
                count = 1

        return curr
```
