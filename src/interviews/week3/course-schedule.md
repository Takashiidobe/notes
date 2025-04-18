# Course Schedule

There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.

    For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.

Return true if you can finish all courses. Otherwise, return false.

Example 1:

```
Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take.
To take course 1 you should have finished course 0. So it is possible.
```

Example 2:

```
Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take.
To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.
```

## Solution

Topological Sort: Find all the courses with no dependencies, take those,
and then update the dependencies of all courses with that course. If any
course no longer has any dependencies, add it to the queue to process
again.

```python
class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        courses_taken = 0
        prereqs = defaultdict(set)
        courses = defaultdict(set)

        for prereq, course in prerequisites:
            prereqs[prereq].add(course)
            courses[course].add(prereq)

        q = deque([i for i in range(numCourses) if i not in courses])

        while q:
            course = q.popleft()
            courses_taken += 1
            for c in prereqs[course]:
                courses[c].remove(course)
                if not courses[c]:
                    q.append(c)

        return courses_taken == numCourses
```
