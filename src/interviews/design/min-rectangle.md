Design a data structure that supports two operations:

`add()` which takes an x and y coordinate:

And `minRectangle()`, which returns the area of the minimum rectangle of
the coordinates currently in the data structure.

For example:

`add(1, 1)`
`minRectangle()` returns 1

`add(4, 4)`
`minRectangle()` returns 9

## Solution

Use two self-balancing trees to keep track of the x and y coordinates.
Have one data structure keep track of the xs, and one data structure
keep track of the ys.

You can calculate the minimum x, maximum x, minimum y, and maximum y
from the data structure.
