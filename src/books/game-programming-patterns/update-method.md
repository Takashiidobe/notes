---
title: update-method
---

Method

# Update Method

## Intent

Simulate a collection of independent objects by telling each to process
one frame of behavior at a time.

Let's create some skeletons that guard an entrance:

```cpp
while(true) {
  for (double x = 0; x < 100; x++) skeleton.setX(x);
  for (double x = 100; x > 0; x--) skeleton.setX(x);
}
```

Of course, the player doesn't see this. It's locked in an infinite
loop.

Instead, we'll rely on the outer loop for iteration.

```cpp
Entity skeleton;
bool patrollingLeft = false;
double x = 0;

while (true) {
  if (patrollingLeft) {
    x--;
    if (x == 0) patrollingLeft = false;
  } else {
    x++;
    if (x == 100) patrollingLeft = true;
  }
  skeleton.setX(x);
}
```

Then we'll have to add some more enchanted statues...

```cpp
Entity leftStatue;
Entity rightStatue;
int leftStatueFrames = 0;
int rightStatueFrames = 0;

// Main game loop:
while (true) {
  if (++leftStatueFrames == 90) {
    leftStatueFrames = 0;
    leftStatue.shootLightning();
  }

  if (++rightStatueFrames == 80) {
    rightStatueFrames = 0;
    rightStatue.shootLightning();
  }

  // Handle user input and render game...
}
```

This is maintainable. We have lots of state stuffed in the game loop.

Instead, _Each entity in the game should encapsulate its own behavior_.

We need an abstraction layer: we create that by defining an abstract
`update()` method. The game loop maintains a collection of objects, and
all it does is call `update()` on them once, every frame.

## The Pattern

The game world maintains a collection of objects. Each object implements
an update method that simulates one frame of the object's behavior.
Each frame, the game updates every object in the collection.

## When to Use It

This pattern works well when:

1.  Your game has a number of objects or systems that need to run
    simultaneously.
2.  Each object's behavior is mostly independent of the others.
3.  The objects need to be simulated over time.

## Keep in Mind

- Splitting code into single frame slices makes it more complex
- You have to store state to resume where you left off each frame
- Objects are updated sequentially. If objects rely on each other's
  state, this can end up in edge cases if both are updated at the same
  time.
- Be careful modifying the object list while updating.
- You can easily handle the case where objects are added to the end of
  the list, but not being removed. If you don't want to update dead
  objects, allow them to be labeled as `dead`. The update loop can
  skip over dead objects, and at the end of the loop, remove them.

## Sample Code

```cpp
class Entity {
  public:
    Entity() : x_(0), y_(0) {}
    virtual ~Entity() {}
    virtual void update = 0;

    double x() const { return x_; }
    double y() const { return y_; }

    void setX(double x) { x_ = x; }
    void setY(double y) { y_ = y; }

  private:
    double x_;
    double y_;
};
```

Then we need a world to hold all of these objects.

```cpp
class World {
  public:
    World() : numEntities_(0) {}
    void gameLoop();
  private:
    Entity* entities_[MAX_ENTITIES];
    int numEntities_;
};
```

And of course, implementing the `gameLoop` method:

```cpp
void World::gameLoop() {
  while (true) {
    for (const auto entity : entities_) {
      entities_.update();
      // code to handle if entities are dead
    }
  }
}
```

## Defining Entities

```cpp
class Skeleton : public Entity {
public:
  Skeleton() : patrollingLeft_(false) {}

  virtual void update() {
    if (patrollingLeft_) {
      setX(x() - 1);
      if (x() == 0) patrollingLeft_ = false;
    }
    else {
      setX(x() + 1);
      if (x() == 100) patrollingLeft_ = true;
    }
  }

private:
  bool patrollingLeft_;
};
```

And the statue:

```cpp
class Statue : public Entity {
public:
  Statue(int delay) : frames_(0), delay_(delay) {}

  virtual void update() {
    if (++frames_ == delay_) {
      shootLightning();

      // Reset the timer.
      frames_ = 0;
    }
  }

private:
  int frames_;
  int delay_;

  void shootLightning() { /* Shoot the lightning... */ }
};
```

If we allow our game to have variable time pass in the game loop, we can
pass that in:

```cpp
void Skeleton::update(double elapsed) {
  if (patrollingLeft_) {
    x -= elapsed;
    if (x <= 0) {
      patrollingLeft_ = false;
      x = -x;
    }
  }
  else {
    x += elapsed;
    if (x >= 100) {
      patrollingLeft_ = true;
      x = 100 - (x - 100);
    }
  }
}
```

## What class does the update method live on?

1.  The entity class:

- This is the simplest option, but it uses inheritance, and can be
  brittle.

2.  The component class:

- If you're using the Component pattern, this makes sense. Each
  component can update itself independently.

3.  A delegate class:

- The state pattern or Type object lets you delegate behavior to
  another object.

## How are dormant objects handled?

Dormant objects can be handled by setting a flag that says whether or
not they're alive (simpler) or you can separate entities into a
collection of alive or not.

Prev: [game-loop](game-loop.md) Next:
[bytecode](bytecode.md)
