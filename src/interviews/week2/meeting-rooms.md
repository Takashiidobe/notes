# Meeting Rooms

Given an array of meeting time intervals consisting of start and end times `[[s1,e1],[s2,e2],...]` `(si< ei)`, determine if a person could attend all meetings.

## Solution

Sort all the meeting times by start time, and see if any meetings
overlap -- if they do, then it is not possible to go to all the
meetings.

```python
class Solution(object):
    def canAttendMeetings(self, intervals):
        if not intervals:
            return True

        intervals.sort()

        for i, (_, end), (next_start, _) in enumerate(zip_longest(intervals, intervals[1:])):
            if i == len(intervals) - 1:
                return True
            if next_start < end:
                return False
```
