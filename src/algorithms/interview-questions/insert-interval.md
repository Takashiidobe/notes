---
title: insert-interval
---

Interval\"

Since we only have to insert one interval here, and our intervals are
already sorted, we can do this in O(n) time by thinking about it as
having three sections:

1.  All intervals that come before the new interval (we\'ll call this
    left)
2.  All intervals that come after the interval (we\'ll call this right).
3.  All intervals that overlap with the new interval

- If the interval\'s end time is before the new interval\'s start
  time, we know that this interval comes before.
- If the interval\'s start time is after the new interval\'s end time,
  we know that this interval comes after.
- Otherwise, we have to do some kind of merge. Since we want to
  subsume all intervals, we will take the minimum starting time and
  the maximum ending time.

```py
def main(intervals, newInterval):
  left = []
  right = []
  mid = [newInterval[0], newInterval[1]]

  for interval in intervals:
      if interval[1] < start:
          left.append(interval)
      elif interval[0] > end:
          right.append(interval)
      else:
          mid[0] = min(mid[0], interval[0])
          mid[1] = max(mid[1], interval[1])

  return left + [mid] + right
```
