You are trying to drive from the top left of a city to the bottom right corner.
Your car can only move to directly to the right or directly down.
The city roads are stored in a 2d matrix of size m*n.
The values at `grid[i][j]` represent the time when that traffic light will turn green (meaning you can access that position).
Return the earliest time you can reach the bottom right corner.

```
[
 [1, 2, 3, 4],
 [2, 2, 2, 1],
 [4, 3, 5, 2]
]

result = 2
```

```
[
 [1, 1, 1, 9],
 [9, 9, 1, 9],
 [1, 1, 1, 9],
 [1, 9, 9, 9],
 [1, 1, 1, 1]
]

result = 1
```

# Approach

This approach requires a set to store visited paths, otherwise it becomes combinatorial to solve the problem.
