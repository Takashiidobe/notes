---
title: flyweight
---

Prev: \[command](command.md) Next:
\[observer](observer.md)

# Flyweight

The Flyweight pattern is used for lowering memory usage by sharing as
much data as possible with other similar objects.

## Forest for the Trees

Let\'s say you want to paint a large amount of trees in a landscape:

```cpp
class Tree {
private:
    Mesh mesh_;
    Texture bark_;
    Texture leaves_;
    Vector position_;
    double height_;
    double thickness_;
    Color barkTint_;
    Color leafTint_;
};
```

We notice that the mesh, bark, and leaves are going to be all the same.
We\'ll leave the barkTint and leafTint as customizable:

```cpp
class TreeModel {
private:
    Mesh mesh_;
    Texture bark_;
    Texture leaves_;
};
```

And our tree will look like this:

```cpp
class Tree {
private:
    TreeModel* model_;

    vector position_;
    double height_;
    double thickness_;
    Color barkTint_;
    Color leafTint_;
};
```

Now, when we want to create a forest, we just provide one TreeModel and
a Vector of Trees, with each tree pointing to a TreeModel.

We split a component into two parts. The parts that are `context-free`,
and the parts that are unique to the instance.

## A Place to Put Down Roots

Let\'s try to put down terrain on the earth.

```cpp
enum class Terrain {
    Grass,
    Hill,
    River
};
```

The world has a grid of these:

```cpp
class World {
private:
    Terrain tiles_[WIDTH][HEIGHT];
}
```

and we get some useful data from a tile like so:

```cpp
int World::getMovementCost(int x, int y) {
  switch (tiles_[x][y]) {
    case TERRAIN_GRASS: return 1;
    case TERRAIN_HILL:  return 3;
    case TERRAIN_RIVER: return 2;
  }
}

bool World::isWater(int x, int y) {
  switch (tiles_[x][y]) {
    case TERRAIN_GRASS: return false;
    case TERRAIN_HILL:  return false;
    case TERRAIN_RIVER: return true;
  }
}
```

Instead, let\'s make a terrain class.

```cpp
class Terrain {
public:
    Terrain(int movementCost, bool isWater, Texture texture)
    : movementCost_(movementConst),
    isWater_(isWater),
    texture_(texture) {}

  int getMovementCost() const { return movementCost_; }
  bool isWater() const { return isWater_; }
  const Texture& getTexture() const { return texture_; }

private:
  int movementCost_;
  bool isWater_;
  Texture texture_;
};
```

Because this has nothing that\'s coupled to the location of the tile,
let\'s just generate one tile of each type and maintain pointers to it
in the world instance.

```cpp
class World {
private:
  Terrain* tiles_[WIDTH][HEIGHT];
};
```

Because this is used in multiple places, hoist the lifetime of these
terrain pieces:

```cpp
class World {
public:
  World()
  : grassTerrain_(1, false, GRASS_TEXTURE),
    hillTerrain_(3, false, HILL_TEXTURE),
    riverTerrain_(2, true, RIVER_TEXTURE)
  {}

private:
  Terrain grassTerrain_;
  Terrain hillTerrain_;
  Terrain riverTerrain_;
};
```

Then we can paint the ground like so:

```cpp
void World::generateTerrain() {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            // Make hills
            if (random(10) == 0) tiles_[x][y] = &hillTerrain_;
            else tiles_[x][y] = &grassTerrain_;
        }
    }
    // Make a river
    int x = random(WIDTH);
    for (int y = 0; y < HEIGHT; y++) {
        tiles_[x][y] = &riverTerrain_;
    }
}
```

Now instead of a method on `World` for accesssing the terrain
properties, expose the Terrain object directly.

```cpp
const Terrain& World::getTile(int x, int y) const {
    return *tiles_[x][y];
}
```

Prev: \[command](command.md) Next:
\[observer](observer.md)
