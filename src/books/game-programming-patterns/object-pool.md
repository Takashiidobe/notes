---
title: object-pool
---

Pool

# Object Pool

## Intent

Improve performance and memory use by reusing objects from a fixed pool
instead of allocating and freeing them individually.

## Motivation

The Object pool pattern allows us to quickly allocate and deallocate
objects.

## The Curse of fragmentation

Imagine you have a 16-byte chunk of memory:

But there\'s one two-byte chunk in the middle, so all you have is an
8-byte chunk and a 6-byte chunk.

You get a request for a 12-byte chunk, which you could allocate size
wise, but you can\'t allocate because you don\'t have a free 12-byte
chunk.

## Keep in Mind

Normally you use `new` and `delete` to handle memory management for you.
Here are some things to keep in mind:

1.  The pool may waste memory on unneeded objects
2.  Only a fixed number of objects can be active at any one time: What
    happens when we need to allocate a new object?

- Prevent it outright: tune pool sizes
- Don\'t create the objects
- Forcibly kill an existing object

## Memory size of each object is fixed

- Arrays only hold items of the same size. Instead of allocating a lot
  of items with small, medium, large sizes, you might want to create
  arrays for small sized objects, medium sized objects, and large
  sized objects.

## Unused objects will remain in memory

- You can\'t use it with garbage collection

## Sample Code

Start by implementing a simple particle class:

```cpp
class Particle {
public:
  Particle()
  : framesLeft_(0)
  {}

  void init(double x, double y,
            double xVel, double yVel, int lifetime) {
    x_ = x; y_ = y;
    xVel_ = xVel; yVel_ = yVel;
    framesLeft_ = lifetime;
  }

  void animate() {
    if (!inUse()) return;

    framesLeft_--;
    x_ += xVel_;
    y_ += yVel_;
  }

  bool inUse() const { return framesLeft_ > 0; }

private:
  int framesLeft_;
  double x_, y_;
  double xVel_, yVel_;
};
```

And then we create a pool that owns all these particles:

```cpp
class ParticlePool {
public:
  void create(double x, double y,
              double xVel, double yVel, int lifetime);

  void animate() {
    for (int i = 0; i < POOL_SIZE; i++) {
      particles_[i].animate();
    }
  }

private:
  static const int POOL_SIZE = 100;
  Particle particles_[POOL_SIZE];
};
```

A new particle can be created as well:

```cpp
void ParticlePool::create(double x, double y,
                          double xVel, double yVel,
                          int lifetime) {
  // Find an available particle.
  for (int i = 0; i < POOL_SIZE; i++) {
    if (!particles_[i].inUse()) {
      particles_[i].init(x, y, xVel, yVel, lifetime);
      return;
    }
  }
}
```

You\'ll notice that every time we want to allocate more memory, this
costs O(n) time to traverse to the end of the pool. We can get away with
using a union and a free list:

```cpp
class Particle {
public:
  // ...

  Particle* getNext() const { return state_.next; }
  void setNext(Particle* next) { state_.next = next; }

private:
  int framesLeft_;

  union {
    // State when it's in use.
    struct {
      double x, y;
      double xVel, yVel;
    } live;

    // State when it's available.
    Particle* next;
  } state_;
};
```

The particle pool keeps a pointer to the first available particle:

```cpp
class ParticlePool {
  // ...
private:
  Particle* firstAvailable_;
};
```

Then we provide a constructor:

```cpp
ParticlePool::ParticlePool() {
  // The first one is available.
  firstAvailable_ = &particles_[0];

  // Each particle points to the next.
  for (int i = 0; i < POOL_SIZE - 1; i++) {
    particles_[i].setNext(&particles_[i + 1]);
  }

  // The last one terminates the list.
  particles_[POOL_SIZE - 1].setNext(NULL);
}
```

And a way to create a particle:

```cpp
void ParticlePool::create(double x, double y,
                          double xVel, double yVel,
                          int lifetime) {
  // Make sure the pool isn't full.
  assert(firstAvailable_ != NULL);

  // Remove it from the available list.
  Particle* newParticle = firstAvailable_;
  firstAvailable_ = newParticle->getNext();

  newParticle->init(x, y, xVel, yVel, lifetime);
}
```

And when a particle dies, we add it back to the free list:

```cpp
bool Particle::animate() {
  if (!inUse()) return false;

  framesLeft_--;
  x_ += xVel_;
  y_ += yVel_;

  return framesLeft_ == 0;
}
```

Threading it back properly:

```cpp
void ParticlePool::animate() {
  for (int i = 0; i < POOL_SIZE; i++) {
    if (particles_[i].animate()) {
      // Add this particle to the front of the list.
      particles_[i].setNext(firstAvailable_);
      firstAvailable_ = &particles_[i];
    }
  }
}
```

Prev: \[dirty-flag](dirty-flag.md) Next:
\[spatial-partition](spatial-partition.md)
