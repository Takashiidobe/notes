# Insert Interval

You are given an array of non-overlapping intervals intervals where intervals[i] = [starti, endi] represent the start and the end of the ith interval and intervals is sorted in ascending order by starti. You are also given an interval newInterval = [start, end] that represents the start and end of another interval.

Insert newInterval into intervals such that intervals is still sorted in ascending order by starti and intervals still does not have any overlapping intervals (merge overlapping intervals if necessary).

Return intervals after the insertion.

Example 1:

```
Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]
```

Example 2:

```
Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
```

## Solution

Since the interval is sorted for us, we can filter the intervals into
three categories:

1. Intersecting with the new interval
2. Before the new interval
3. After the new interval

If the times are intersecting with the new interval, the new interval
widens to the minimum times of both intervals, and the maximum times of
both intervals.

```python
class Solution:
    def insert(self, intervals: List[List[int]], newInterval: List[int]) -> List[List[int]]:
        left, right, start, end = [], [], *newInterval

        for interval in intervals:
            if interval[1] < start:
                left.append(interval)
            elif interval[0] > end:
                right.append(interval)
            else:
                start = min(start, interval[0])
                end = max(end, interval[1])

        return left + [[start, end]] + right
```
