# Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.

# An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.

# You may assume all four edges of the grid are all surrounded by water.

"""
Input: grid = [
["1","1","1","1","0"],
["1","1","0","1","0"],
["1","1","0","0","0"],
["0","0","0","0","0"]
]
Output: 1

Input: grid = [
["1","1","0","0","0"],
["1","1","0","0","0"],
["0","0","1","0","0"],
["0","0","0","1","1"]
]
Output: 3
"""

"""

1. Assume the grid is at least 1 x 1 and never null.
2. I can mutate the array passed in.
3. the inputs are always a string '1' or '0'.
   """

"""

def count_islands(grid: List[List[str]]) -> int:
m = len(grid)
n = len(grid[0])

    def dfs(grid: List[List[str]], i: int, j: int):
        nonlocal m, n
        if i < 0 or j < 0 or i >= m or j >= n:
            return None

        if grid[i][j] == '1':
            grid[i][j] = '0'
            dfs(grid, i, j - 1)
            dfs(grid, i, j + 1)
            dfs(grid, i - 1, j)
            dfs(grid, i + 1, j)

    count = 0

    for i in range(m):
        for j in range(n):
            if grid[i][j] == '1':
                count += 1
                dfs(grid, i, j)

    return count

"""

"""
Given a two-dimensional integer matrix of 1s and 0s, return the number of distinct "islands" in the matrix.
A 1 represents land and 0 represents water, so an island is a group of 1s that are neighboring whose perimeter is surrounded by water.
Two islands are distinct if their shapes are different.

matrix = [
[1, 0, 0, 0, 0],
[0, 0, 1, 1, 0],
[0, 1, 1, 0, 0],
[0, 0, 0, 0, 0],
[1, 1, 0, 1, 1],
[1, 1, 0, 1, 1]
]
3 2 1


# 1 1 1 # 3

# 1 1 # 2

# 1 # 1

matrix = [
[1, 0, 0, 1, 1],
[1, 1, 0, 0, 0],
[0, 1, 1, 0, 0],
[0, 0, 0, 0, 0],
[1, 1, 0, 1, 1],
[1, 1, 0, 1, 1]
]
2 3 1
1 [0, 1, 0],
2 [1, 1, 0],
2 [0, 1, 1],

Output = 3

1. Islands with the same shape are counted once. We care about the layout of the islands.

Criteria for same shape

1. block count must be the shape for both islands.
2. Count by row and column length/width # i could keep some visited set for the island size and generate a 2d matrix of row/col widths.

https://binarysearch.com/problems/Distinct-Islands
"""


# < m _ n _

def coordinates_to_list(coordinates: set, m: int, n: int) -> (List[int], List[int]):
min_x = m
max_x = 0
min_y = n
max_y = 0

    for coordinate in coordinates:
        # set min_x and max_x and

# m \* n

def count_islands(grid: List[List[str]]) -> int:
m = len(grid)
n = len(grid[0])
visited = set()
island_shapes = set()
curr = set()

    def dfs(grid: List[List[str]], i: int, j: int):
        nonlocal m, n, visited, curr
        if i < 0 or j < 0 or i >= m or j >= n or (i, j) in visited:
            return None

        if grid[i][j] == '1':
            visited.add((i, j))
            curr.add((i, j))
            dfs(grid, i, j - 1)
            dfs(grid, i, j + 1)
            dfs(grid, i - 1, j)
            dfs(grid, i + 1, j)


    for i in range(m):
        for j in range(n):
            if grid[i][j] == '1':
                dfs(grid, i, j)
                # some logic to calculate the m x n array of count of 1s
                island_set.add(frozenset(rows_and_cols))
                curr = set()

    return len(island_shapes)
