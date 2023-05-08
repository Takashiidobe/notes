# Find Median from Data Stream

## Solution

```python
from sortedcontainers import SortedList

class MedianFinder:
    def __init__(self):
        self.nums = SortedList()
        self.len = 0

    def addNum(self, num: int) -> None:
        self.nums.add(num)
        self.len += 1

    def findMedian(self) -> float:
        if self.len % 2:
            return self.nums[self.len // 2]
        else:
            left = self.nums[self.len // 2 - 1]
            right = self.nums[self.len // 2]
            return (left + right) / 2
```
