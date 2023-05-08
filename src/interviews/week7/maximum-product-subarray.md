# Maximum Product Subarray

## Solution

```python
class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        max_product = max_so_far = min_so_far = nums[0]

        for curr_num in nums[1:]:
            choices = [curr_num, max_so_far * curr_num, min_so_far * curr_num]
            min_so_far = min(choices)
            max_so_far = max(choices)

            max_product = max(max_product, max_so_far)

        return max_product
```
