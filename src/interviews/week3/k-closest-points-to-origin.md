# K Closest Points to Origin
Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane and an integer k, return the k closest points to the origin (0, 0).

The distance between two points on the X-Y plane is the Euclidean distance (i.e., √(x1 - x2)2 + (y1 - y2)2).

You may return the answer in any order. The answer is guaranteed to be unique (except for the order that it is in).

Example 1:

```
Input: points = [[1,3],[-2,2]], k = 1
Output: [[-2,2]]
Explanation:
The distance between (1, 3) and the origin is sqrt(10).
The distance between (-2, 2) and the origin is sqrt(8).
Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
We only want the closest k = 1 points from the origin, so the answer is just [[-2,2]].
```

Example 2:

```
Input: points = [[3,3],[5,-1],[-2,4]], k = 2
Output: [[3,3],[-2,4]]
Explanation: The answer [[-2,4],[3,3]] would also be accepted.
```

## Solution

To calculate the K closest points to origin, there are a few solutions:

The simplest one is to return the top k points from a list based on
sorting with euclidean distance. This is O (n log n) because it requires
sorting the entire list.

```python
from sortedcontainers import SortedList

class Solution:
    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        return SortedList(points, key=lambda x: abs(x[0]) ** 2 + abs(x[1]) ** 2)[:k]
```

A better solution involves putting all the points in a heap and
returning the k smallest points for O(n log k) complexity.

```python
class Solution:
    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        return nsmallest(k, points, key=lambda x: abs(x[0]) ** 2 + abs(x[1]) ** 2)
```

The best algorithm involves using quickselect for an average of O(n)
time (nth_element is not a python function, so it won't work here).

```python
class Solution:
    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        return nth_element(points, k, key=lambda x: abs(x[0]) ** 2 + abs(x[1]) ** 2)
```
