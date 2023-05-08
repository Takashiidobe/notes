# Rotting Oranges

You are given an m x n grid where each cell can have one of three values:

    0 representing an empty cell,
    1 representing a fresh orange, or
    2 representing a rotten orange.

Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.

Example 1:

```
Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
Output: 4
```

Example 2:

```
Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation: The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.
```

Example 3:

```
Input: grid = [[0,2]]
Output: 0
Explanation: Since there are already no fresh oranges at minute 0, the answer is just 0.
```

## Solution

To count the amount of time that it takes to make all the oranges
rotten, we start off by dividing the oranges into three, the empty
square(which we can disregard), the rotten squares (where we will
4-dimensionally rot all fresh oranges each turn) and the fresh oranges.

Every tick, go to each of the rotting oranges and make oranges rot if
they haven't. Then, if all squares are rotten or empty, return the time.

If no more oranges have rotted this tick, we know that we can't make all
the oranges rotten. Return -1.

```python
class Solution:
    def orangesRotting(self, grid: List[List[int]]) -> int:
        minute = 0
        m = len(grid)
        n = len(grid[0])
        empty = set((y, x) for y in range(m) for x in range(n) if grid[y][x] == 0)
        rotten = set((y, x) for y in range(m) for x in range(n) if grid[y][x] == 2)

        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

        def inbounds(x, y):
            return 0 <= y < m and 0 <= x < n

        def valid(x, y):
            return (y, x) not in empty and (y, x) not in rotten and inbounds(x, y)

        while True:
            if len(empty) + len(rotten) == m * n:
                return minute
            new_rotten = set()
            minute += 1
            for y, x in rotten:
                for dy, dx in directions:
                    new_y, new_x = dy + y, dx + x
                    if valid(new_x, new_y):
                        new_rotten.add((new_y, new_x))
            if not new_rotten:
                return -1
            rotten.update(new_rotten)
```
