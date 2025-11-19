---
title: data-locality
---

Locality

# Data Locality

## Intent

Accelerate memory access by arranging data to take advantage of CPU
caching.

## Motivation

While Moore's law has been making processors faster, memory access has
plateaued in speed: we can process data faster with each passing year,
but we can't get it much faster.

With today's hardware, it can take hundreds of cycles to fetch a byte
of data from RAM.

### A pallet for your CPU

As memory access speeds stalled, hardware engineers found CPU caching to
make memory access faster. Modern computers have memory inside the chip.
It's extremely small (sometimes called SRAM, for Static RAM, or L1
cache). It might hold 128 bytes. When the CPU seeks for data in RAM, it
pulls the data you want along with its adjacent 128 bytes of data. If
the next instruction operates on data in the cache, it's called a cache
hit -- it already has the data it needs in its cache and is ready to
move on. If it doesn't, it has to go back to RAM, which can take a few
hundred cycles:

If we get a cache hit, our code looks like this:

```cpp
for (const auto& item: items) {
  item.doStuff();
}
```

If we get a cache miss, it's more like this:

```cpp
for (const auto& item: items) {
  sleepFor500Cycles();
  item.doStuff();
}
```

It goes without saying that we want to get rid of that
`sleepFor500Cycles` call.

## Wait, data is performance?

The author wrote the same programs, but with one missing the cache and
the other hitting the cache. The result? The programs that hit the cache
were 50x faster.

Data is performance.

This is why people prefer arrays to lists -- the next item of a list
might be in a random place in memory, which causes a cache miss while
iterating. A vector contiguously lays out its items, resulting in fewer
cache misses.

## The Pattern

Modern CPUs have caches to speed up memory access adjacent to recently
accessed memory. Keep the data in contiguous memory in the order that
you process it.

## When to Use It

You want to use it to speed up memory accesses, but profile before you
employ this technique.
[Cachegrind](https://www.valgrind.org/docs/manual/cg-manual.html.md) is
a good profiling tool to check for cache usage.

## Keep in Mind

In C++ and higher level languages, abstractions generally cost pointer
accesses. A pointer access is almost always a cache miss. Thus, you'll
have to sacrifice some inheritance, interfaces, and other niceties to
use this pattern. It's a tradeoff of simplicity for performance.

## Sample Code

## Contiguous arrays

Instead of doing something like this:

```cpp
class GameEntity { /* Implementation here */ }
class AIComponent {}
class PhysicsComponent {}
class RenderComponent {}

while (!gameOver) {
  // Process AI.
  for (int i = 0; i < numEntities; i++) {
    entities[i]->ai()->update();
  }

  // Update physics.
  for (int i = 0; i < numEntities; i++) {
    entities[i]->physics()->update();
  }

  // Draw to screen.
  for (int i = 0; i < numEntities; i++) {
    entities[i]->render()->render();
  }
  // Other game loop machinery for timing...
}
```

Which thrashes the cache, we'll put everything in an array of
`AiComponents`, `PhysicsComponents` and `RenderComponents`.

```cpp
AIComponent* aiComponents = new AIComponent[MAX_ENTITIES];
PhysicsComponent* physicsComponents = new PhysicsComponent[MAX_ENTITIES];
RenderComponent* renderComponents = new RenderComponent[MAX_ENTITIES];
```

Instead of using pointers, we'll directly update each.

```cpp
while (!gameOver) {
  // Process AI.
  for (int i = 0; i < numEntities; i++) {
    aiComponents[i].render();
  }

  // Update physics.
  for (int i = 0; i < numEntities; i++) {
    physicsComponents[i].render();
  }

  // Draw to screen.
  for (int i = 0; i < numEntities; i++) {
    renderComponents[i].render();
  }
  // Other game loop machinery for timing...
}
```

### Packed Data

We can do the same with our Particles too:

```cpp
class Particle {}
```

Instead of adding a flag if its active and checking on that flag:

```cpp
for (int i = 0; i < numParticles_; i++) {
  if (particles_[i].isActive()) {
    particles_[i].update();
  }
}
```

We sort the active particles to the beginning of the buffer (or we have
two sets, the active and inactive)

Then, we have no branching at all:

```cpp
for (int i = 0; i < numActive_; i++) {
  particles[i].update();
}
```

### Hot/Cold Splitting

What happens if you have a game entity, where it has some commonly used
fields and some uncommonly used fields?

```cpp
class AIComponent {
public:
  void update() {}
private:
// commonly used
  Animation* animation_;
  double energy_;
  Vector goalPos_;
// uncommonly used
  LootType drop_;
  int minDrops_;
  int maxDrops_;
  double chanceOfDrop_;
};
```

Split it into two separate pieces, and point to the cold part with a
pointer:

```cpp
class AIComponent {
public:
  // Methods...
private:
  Animation* animation_;
  double energy_;
  Vector goalPos_;

  LootDrop* loot_;
};

class LootDrop {
  friend class AIComponent;
  LootType drop_;
  int minDrops_;
  int maxDrops_;
  double chanceOfDrop_;
};
```

This can be helpful, but for less clear cut cases, less useful.

## Design Decisions

This pattern is about a mindset, and applying it to code that's slow.

### How do you handle polymorphism?

- Don't

  - It's safe and easy
  - It's faster
  - It's inflexible

- Use Separate arrays for each type

  - It keeps objects tightly packaged
  - You can use static dispatch
  - You have to keep track of more collections
  - You have to be aware of every type

- Use a collection of pointers

  - It's flexible
  - It's less cache friendly

### How are game entities defined?

- If game entities are classes with pointers to their components

  - You can store components in contiguous arrays
  - Given an entity, you can easily get to its components
  - Moving components in memory is hard

- If game entities are classes with IDs for their components

  - It's more complex
  - It's slower
  - You'll need access to the "component" manager.

- If the game entity itself is just an ID

  - Entities are tiny
  - Entities are empty
  - You don't have to manage their lifetime
  - Looking up a component is slower

Prev: [service-locator](service-locator.md) Next: [dirty-flag](dirty-flag.md)
