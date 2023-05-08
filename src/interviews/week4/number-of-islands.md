# Number of Islands

Given an m x n 2D binary grid `grid` which represents a map of '1's (land) and '0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example 1:

```
Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1
```

Example 2:

```
Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3
```

## Solution

We can do this many ways: union find is one, where each node points to a
parent node, and we calculate the amount of parents in each node.

```python
class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        m = len(grid)
        n = len(grid[0])

        parents = {(y, x): (y, x) for y in range(m) for x in range(n) if grid[y][x] == "1"}

        self.count = len(parents)

        def find(x):
            if x != parents[x]:
                return find(parents[x])
            return x

        def union(x, y):
            x, y = find(x), find(y)
            if x != y:
                if x > y:
                    parents[x] = y
                else:
                    parents[y] = x
                self.count -= 1

        for y in range(m):
            for x in range(n):
                if grid[y][x] == '1':
                    if y + 1 < m and grid[y + 1][x] == '1':
                        union((y, x), (y + 1, x))
                    if x + 1 < n and grid[y][x + 1] == '1':
                        union((y, x), (y, x + 1))

        return self.count
```
