# Pacific Atlantic Water Flow

There is an m x n rectangular island that borders both the Pacific Ocean and Atlantic Ocean. The Pacific Ocean touches the island's left and top edges, and the Atlantic Ocean touches the island's right and bottom edges.

The island is partitioned into a grid of square cells. You are given an `m x n` integer matrix heights where `heights[r][c]` represents the height above sea level of the cell at coordinate `(r, c)`.

The island receives a lot of rain, and the rain water can flow to neighboring cells directly north, south, east, and west if the neighboring cell's height is less than or equal to the current cell's height. Water can flow from any cell adjacent to an ocean into the ocean.

Return a 2D list of grid coordinates result where `result[i] = [ri, ci]` denotes that rain water can flow from cell `(ri, ci)` to both the Pacific and Atlantic oceans.

Example 1:

```
Input: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
```

Example 2:

```
Input: heights = [[2,1],[1,2]]
Output: [[0,0],[0,1],[1,0],[1,1]]
```

## Solution

```python
class Solution:
    def pacificAtlantic(self, heights: List[List[int]]) -> List[List[int]]:
        m, n = len(heights), len(heights[0])
        pacific, atlantic = set(), set()

        def inbounds(y, x):
            return 0 <= y < m and 0 <= x < n

        def dfs(y, x, visited, ocean):
            if (y, x) in visited:
                return
            visited.add((y, x))
            ocean.add((y, x))
            for dy, dx in [(0, 1), (1, 0), (-1, 0), (0, -1)]:
                new_y, new_x = dy + y, dx + x
                if inbounds(new_y, new_x) and heights[y][x] <= heights[new_y][new_x]:
                    dfs(new_y, new_x, visited, ocean)

        for y in range(m):
            for x in range(n):
                if y == 0 or x == 0:
                    dfs(y, x, set(), pacific)
                if y == m - 1 or x == n - 1:
                    dfs(y, x, set(), atlantic)

        return pacific & atlantic
```
