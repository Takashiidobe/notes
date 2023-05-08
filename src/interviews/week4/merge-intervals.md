# Merge Intervals

Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.

Example 1:

```
Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].
```

Example 2:

```
Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.
```

## Solution

To merge all intervals, sort them by their starting time, and if the
current time overlaps with the previous interval encountered, merge
them. Otherwise, add it to the resulting array.

```python
class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        intervals.sort()
        res = [intervals[0]]
        for curr_start, curr_end in intervals[1:]:
            prev_start, prev_end = res[-1]
            if prev_end >= curr_start:
                res[-1] = [min(prev_start, curr_start), max(prev_end, curr_end)]
            else:
                res.append([curr_start, curr_end])
        return res
```
