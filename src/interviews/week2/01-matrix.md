# 01 Matrix

Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.

The distance between two adjacent cells is 1.

Example 1:

```
Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
Output: [[0,0,0],[0,1,0],[0,0,0]]
```

Example 2:

```
Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
Output: [[0,0,0],[0,1,0],[1,2,1]]
```

## Solution

We can do this with dfs or bfs. We copy over the matrix, and then
replace all `1`s with a distance of `float('inf')` since we don't know
their distance, and enqueue the squares with 0s to our queue.

With the 0s in our queue, we can flood fill out, terminating when we
encounter a square where the distance is less than what we could offer.

```python
class Solution:
    def updateMatrix(self, mat: List[List[int]]) -> List[List[int]]:
        m = len(mat)
        n = len(mat[0])
        ans = mat.copy()
        dirs = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        q = deque()

        for y in range(m):
            for x in range(n):
                if ans[y][x] == 1:
                    ans[y][x] = float('inf')
                else:
                    q.append((y, x))

        def inbounds(y, x):
            return 0 <= y < m and 0 <= x < n

        while q:
            y, x = q.popleft()
            for dy, dx in dirs:
                new_y, new_x = dy + y, dx + x
                if inbounds(new_y, new_x) and ans[new_y][new_x] > ans[y][x] + 1:
                    ans[new_y][new_x] = ans[y][x] + 1
                    q.append((new_y, new_x))

        return ans
```
