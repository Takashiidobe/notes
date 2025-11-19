---
title: spatial-partition
---
# Spatial partition

## Intent

Effectively locate objects by storing them in a data structure organized
by their positions.

## Motivation

You'll want to separate out objects on a notion of time and space. A
dead object shouldn't be talking, and you shouldn't hear an object far
away talking either. If you have to iterate through every object to
check its location, it can become a performance bottleneck.

### Units of the field of battle

Let's say we're making an RTS. opposing armies with hundreds of units
will clash on the field of battle. The naive way to handle this is by
looking at every pair of units and seeing how close they are to each
other:

```cpp
void handleMelee(Unit* units[], int numUnits) {
  for (int a = 0; a < numUnits - 1; a++) {
    for (int b = a + 1; b < numUnits; b++) {
      if (units[a]->position() == units[b]->position()) {
        handleAttack(units[a], units[b]);
      }
    }
  }
}
```

This is an O(n^2) algorithm, which quickly becomes too expensive with a
large amount of units.

### Drawing battle lines

The problem that we're running into is that there's no underlying
order to the array of units. Instead of having a 2D battlefield, imagine
that it is a 1D battle line.

Let's try to make a 2D battlefield sortable in a 1D field.

## The Pattern

For a set of objects, each has a position in space. Store them in a
spatial data structure that organizes the objects by their positions.
This data structure lets you efficiently query for objects at or near a
location. When an object's position changes, update the spatial data
structure so that it can continue to find the object.

### When to Use It

This is commonly used for storing live, moving game objects. Use it when
you are querying for objects by location and your performance is
suffering.

### Keep in Mind

Spatial partitions knock an O(n) or O(n^2) operation down to something
more manageable. The more objects you have, the more valuable that
becomes.

Since this pattern involves organizing objects by their positions,
objects that **change** position are harder to deal with.

A spatial partition uses additional memory for its bookkeeping data
structures. It trades **memory** for **speed**. If you can't spare the
memory, this pattern won't help you.

## Sample Code

This pattern's implementation varies: let's start off with a fixed
grid.

### A sheet of graph paper

Imagine the entire field of battle as a matrix. Units that are close
enough to fight are in the same grid. We put all units that are adjacent
to each other in the same cell in the matrix.

Let's implement it.

### A grid of linked units

Let's get coding.

```cpp
class Unit {
  friend class Grid;

public:
  Unit(Grid* grid, double x, double y)
  : grid_(grid),
    x_(x),
    y_(y)
  {}

  void move(double x, double y);

private:
  double x_, y_;
  Grid* grid_;
};
```

Each unit has a position in 2D and a pointer to the grid that it lives
on.

here's the grid:

```cpp
class Grid {
public:
  Grid() {
    // Clear the grid.
    for (int x = 0; x < NUM_CELLS; x++) {
      for (int y = 0; y < NUM_CELLS; y++) {
        cells_[x][y] = NULL;
      }
    }
  }

  static const int NUM_CELLS = 10;
  static const int CELL_SIZE = 20;
private:
  Unit* cells_[NUM_CELLS][NUM_CELLS];
};
```

Now, since every unit should be a linked list, we'll extend unit with
`next` and `prev` pointers.

```cpp
class Unit {
  // Previous code...
private:
  Unit* prev_;
  Unit* next_;
};
```

### Entering the field of battle

Next, we'll want to make sure that new units are placed in the grid on
construction:

```cpp
Unit::Unit(Grid* grid, double x, double y)
: grid_(grid),
  x_(x),
  y_(y),
  prev_(NULL),
  next_(NULL) {
  grid_->add(this);
}
```

With the `add()` method defined like so:

```cpp
void Grid::add(Unit* unit) {
  // Determine which grid cell it's in.
  int cellX = (int)(unit->x_ / Grid::CELL_SIZE);
  int cellY = (int)(unit->y_ / Grid::CELL_SIZE);

  // Add to the front of list for the cell it's in.
  unit->prev_ = NULL;
  unit->next_ = cells_[cellX][cellY];
  cells_[cellX][cellY] = unit;

  if (unit->next_ != NULL) {
    unit->next_->prev_ = unit;
  }
}
```

### A clash of swords

Once all of the units are nestled in their cells, let's have them
fight:

```cpp
void Grid::handleMelee() {
  for (int x = 0; x < NUM_CELLS; x++) {
    for (int y = 0; y < NUM_CELLS; y++) {
      handleCell(cells_[x][y]);
    }
  }
}
```

```cpp
void Grid::handleCell(Unit* unit) {
  while (unit != NULL) {
    Unit* other = unit->next_;
    while (other != NULL) {
      if (unit->x_ == other->x_ &&
          unit->y_ == other->y_) {
        handleAttack(unit, other);
      }
      other = other->next_;
    }

    unit = unit->next_;
  }
}
```

Aside from having to traverse a linked list, we've partitioned the
battlefield into little isolated skirmishes.

### Charging forward

We have no code for moving a unit between cells. Let's fix that:

Let's define a method for that:

```cpp
void Unit::move(double x, double y) {
  grid_->move(this, x, y);
}
```

And then add it to the Grid.

```cpp
void Grid::move(Unit* unit, double x, double y) {
  // See which cell it was in.
  int oldCellX = (int)(unit->x_ / Grid::CELL_SIZE);
  int oldCellY = (int)(unit->y_ / Grid::CELL_SIZE);

  // See which cell it's moving to.
  int cellX = (int)(x / Grid::CELL_SIZE);
  int cellY = (int)(y / Grid::CELL_SIZE);

  unit->x_ = x;
  unit->y_ = y;

  // If it didn't change cells, we're done.
  if (oldCellX == cellX && oldCellY == cellY) return;

  // Unlink it from the list of its old cell.
  if (unit->prev_ != NULL) {
    unit->prev_->next_ = unit->next_;
  }

  if (unit->next_ != NULL) {
    unit->next_->prev_ = unit->prev_;
  }

  // If it's the head of a list, remove it.
  if (cells_[oldCellX][oldCellY] == unit) {
    cells_[oldCellX][oldCellY] = unit->next_;
  }

  // Add it back to the grid at its new cell.
  add(unit);
}
```

If we move but don't cross a cell boundary, we return there. Otherwise,
we unlink the node from its current location and then add it back to the
grid at its new cell.

### At arm's length

This works, but only for units with a melee range. What happens for
ranged units?

Let's handle ranged units like so:

```cpp
if (distance(unit, other) < ATTACK_DISTANCE) {
  handleAttack(unit, other);
}
```

```cpp
void Grid::handleUnit(Unit* unit, Unit* other) {
  while (other != NULL) {
    if (distance(unit, other) < ATTACK_DISTANCE) {
      handleAttack(unit, other);
    }

    other = other->next_;
  }
}
```

Then have the grid handle units that are in the cell:

```cpp
void Grid::handleCell(int x, int y) {
  Unit* unit = cells_[x][y];
  while (unit != NULL) {
    // Handle other units in this cell.
    handleUnit(unit, unit->next_);

    unit = unit->next_;
  }
}
```

And neighboring cells:

```cpp
void Grid::handleCell(int x, int y) {
  Unit* unit = cells_[x][y];
  while (unit != NULL) {
    // Handle other units in this cell.
    handleUnit(unit, unit->next_);

    // Also try the neighboring cells.
    if (x > 0 && y > 0) handleUnit(unit, cells_[x - 1][y - 1]);
    if (x > 0) handleUnit(unit, cells_[x - 1][y]);
    if (y > 0) handleUnit(unit, cells_[x][y - 1]);
    if (x > 0 && y < NUM_CELLS - 1) {
      handleUnit(unit, cells_[x - 1][y + 1]);
    }

    unit = unit->next_;
  }
}
```

We have to make sure to only handle half of the cells around each unit.
If we handled all adjacent nodes, we would get a situation where a unit
could attack one unit when scanning for nearby enemies, and when the
nearby enemy scans, that unit would be attacked again.

## Design Decisions

We went through an example using a matrix, but quadtrees and Binary
space partitions (BSPs) are commonly used in place of them.

### Is the partition hierarchical or flat?

- If it's flat

  - It's simpler
  - Memory usage is constant
  - It can be faster to update when objects change their positions

- If it's hierarchical

  - It handles empty space more efficiently
  - It handles densely populated areas more efficiently.

### Does the partitioning depend on the set of objects?

- If the partitioning is object-independent

  - Objects can be moved quickly
  - The partitions can be imbalanced

- If the partitioning adapts to the set of objects

  - You can ensure the partitions are balanced
  - It's more efficient to partition an entire set of objects at
    once.

- If the partitioning is object-independent, but hierarchy is
  object-dependent

  - A quadtree starts out with a single partition. When the amount
    of objects exceeds this, it recursively splits into 4
    partitions. Thus:
  - Objects can be added incrementally
  - Objects can be moved quickly
  - Partitions are balanced

### Are objects only stored in the partition?

You can store the object in the partition, or a secondary cache to make
look-up faster.

- If it is the only place objects are stored:

  - It avoids the memory overhead and complexity of two collections

- If there is another collection for the objects

  - Traversing objects is faster

## See Also

Here are some of the common structures for Spatial partitions.

- [Grid](<https://en.wikipedia.org/wiki/Grid_(spatial_index).md>)
- [Quadtree](http://en.wikipedia.org/wiki/Quad_tree.md)
- [BSP](http://en.wikipedia.org/wiki/Binary_space_partitioning.md)
- [K-d tree](http://en.wikipedia.org/wiki/Kd-tree.md)
- [Bounding volume
  hierarchy](http://en.wikipedia.org/wiki/Bounding_volume_hierarchy.md)

Prev: [object-pool](object-pool.md)
