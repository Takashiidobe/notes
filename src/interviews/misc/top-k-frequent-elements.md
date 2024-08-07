Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.

Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Example 2:

Input: nums = [1], k = 1
Output: [1]

Constraints:

    1 <= nums.length <= 105
    k is in the range [1, the number of unique elements in the array].
    It is guaranteed that the answer is unique.

Follow up: your algorithm's time complexity must be better than O(n log n), where n is the array's size.

```python
from collections import Counter

class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        return [x[0] for x in Counter(nums).most_common(k)]
```
