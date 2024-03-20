# 452. Minimum Number of Arrows to Burst Balloons

There are some spherical balloons taped onto a flat wall that represents the XY-plane. The balloons are represented as a 2D integer array points where points[i] = [xstart, xend] denotes a balloon whose horizontal diameter stretches between xstart and xend. You do not know the exact y-coordinates of the balloons.

Arrows can be shot up directly vertically (in the positive y-direction) from different points along the x-axis. A balloon with xstart and xend is burst by an arrow shot at x if `xstart <= x <= xend.` There is no limit to the number of arrows that can be shot. A shot arrow keeps traveling up infinitely, bursting any balloons in its path.

Given the array points, return the minimum number of arrows that must be shot to burst all balloons.

```
Example 1:

Input: points = [[10,16],[2,8],[1,6],[7,12]]
Output: 2
Explanation: The balloons can be burst by 2 arrows:
- Shoot an arrow at x = 6, bursting the balloons [2,8] and [1,6].
- Shoot an arrow at x = 11, bursting the balloons [10,16] and [7,12].

Example 2:

Input: points = [[1,2],[3,4],[5,6],[7,8]]
Output: 4
Explanation: One arrow needs to be shot for each balloon for a total of 4 arrows.

Example 3:

Input: points = [[1,2],[2,3],[3,4],[4,5]]
Output: 2
Explanation: The balloons can be burst by 2 arrows:
- Shoot an arrow at x = 2, bursting the balloons [1,2] and [2,3].
- Shoot an arrow at x = 4, bursting the balloons [3,4] and [4,5].
```

Constraints:

```
1 <= points.length <= 105
points[i].length == 2
-231 <= xstart < xend <= 231 - 1
```

## Intuition

This problem boils down to plotting points on a number line. The
balloons are some arbitrary points with a width of x[0]..x[1] and they
can all be thought of as on the same points on the Y-axis. 

We want to calculate the overlap between balloons. The best way to do
that is to sort them based on their x[0], and then compare each one to
its neighbor. If they have overlap, you want to carry that overlap onto
the next item. When you can no longer find overlap, you need a new arrow
to break the next balloon, and you can reserve an arrow for that case.

Translated to code, that looks like the following:

```python
class Solution:
    def findMinArrowShots(self, points: List[List[int]]) -> int:
        if not points:
            return 0

        points.sort()

        arrows = 1
        left = points[0]

        for right in points[1:]:
            if left[1] >= right[0]:
                left[0] = right[0]
                left[1] = min(left[1], right[1])
            else:
                arrows += 1
                left = right
        
        return arrows
```

