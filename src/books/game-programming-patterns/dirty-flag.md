---
title: dirty-flag
---

Flag

# Dirty Flag

## Intent

Avoid unnecessary work by deferring it until the result is needed.

## Motivation

We want to defer an expensive calculation until it\'s necessary.

Imagine a `scene graph` in a game. This represents the world, and
contains all objects in said world. The rendering engine uses this to
determine where to draw stuff on the screen.

A scene graph is a flat list of objects. Each object has a model, and a
transform. The transform describes the object\'s position, rotation, and
scale in the world. To move or turn an object, we simply change its
transform.

This would be simple, but some objects are anchored to other objects.
Imagine this example: A parrot rests on a pirate\'s shoulder, and the
pirate is in the crow\'s nest of a ship. If the ship moves, all objects
anchored to it should move too. This prevents us from independently
moving each object when the ship moves (which is tedious and error
prone).

## Local and world transforms

To calculate an object\'s world transform, you just walk its parent
chain starting at the root all the way down to the object, combining
transforms as you go.

Basically, the parrot\'s world transform is:

```sh
parrot = ship x nest x pirate x parrot
```

We could calculate every object\'s position every frame, but most
objects don\'t move every frame, so this is a waste of CPU. Let\'s cache
it.

## Cached world transforms

We can cache each object. We store its local transform and its derived
world transform. Great. Now objects that aren\'t updated don\'t require
any updating.

If we calculate an action on the ship, here\'s what actually happens:

    move ship
      recalc ship
        recalc nest
          recalc pirate
            recalc parrot

    move nest
      recalc nest
        recalc pirate
          recalc parrot

    move pirate
      recalc pirate
        recalc parrot

    move parrot
      recalc parrot

This takes us polynomial time to update! This is way too slow.

## Deferred calculation

Let\'s decouple local transforms from the world transforms.

Let\'s add a flag to each object in the graph. When the local transform
changes, we set it. When we need the object\'s world transform, we check
the flag. If it\'s set, we calculate the world transformation and clear
the flag. That way, when it comes time, we can calculate everything once
in a batch, instead of independently.

With this pattern, the game does this:

    -> Move Ship
    -> Move Nest
    -> Move Pirate
    -> Move Parrot

    Render
      Recalc Ship
        Recalc Nest
          Recalc Pirate
            Recalc Parrot

With a single bit of data, we get these three benefits:

- All objects have their position recalculated once.
- Objects that didn\'t move aren\'t recalculated.
- If an object gets removed before it\'s rendered, it doesn\'t
  calculate its world transform at all.

## The Pattern

A set of primary data changes over time. A set of derived data is
determined from this using some expensive process. A "dirty" flag tracks
when the derived data is out of sync with the primary data. It is set
when the primary data changes. If the flag is set when the derived data
is needed, then it is reprocessed and the flag is cleared. Otherwise,
the previous cached derived data is used.

## When to Use It

- This is pretty specific. You should use this pattern sparingly.

Requirements:

- The primary data has to change more often than the derived data is
  used.
- It should be hard to update incrementally.

## Keep in Mind

- There is a cost to deferring for too long

If we recalculate just before we need it, if the operation fails or
takes too long, we\'ll have a visible pause for the user.

Editors auto-save in the background to combat this.

This is basically a GC problem. Refcounting frees memory when it\'s no
longer needed, but burns CPU time updating ref counts eagerly every time
the refcount changes.

Simple garbage collectors defer reclaiming memory until it\'s really
needed.

### You have to make sure to set the flag every time the state changes

- You must always set the flag when it is out of sync with the source
  data.

### You have to keep the previous derived data in memory

- You have to have some representation of the derived data in memory,
  since non-updated data uses this pattern.

## Sample Code

```cpp
class Transform {
public:
  static Transform origin();

  Transform combine(Transform& other);
};
```

We\'ll use combine to get an object\'s world transform by combining all
the local transforms along it\'s parent chain.

Next, let\'s sketch out a graph node that represents an object in the
scene graph.

```cpp
class GraphNode {
public:
  GraphNode(Mesh* mesh)
  : mesh_(mesh),
    local_(Transform::origin())
  {}

private:
  Transform local_;
  Mesh* mesh_;

  GraphNode* children_[MAX_CHILDREN];
  int numChildren_;
};
```

## An unoptimized traversal

Let\'s start off with a basic traversal for rendering the scene graph

```cpp
void GraphNode::render(Transform parentWorld) {
  Transform world = local_.combine(parentWorld);

  if (mesh_) renderMesh(mesh_, world);

  for (int i = 0; i < numChildren_; i++) {
    children_[i]->render(world);
  }
}
```

Then let\'s run the transform:

```cpp
graph_->render(Transform::origin());
```

## Let\'s get dirty

```cpp
class GraphNode {
public:
  GraphNode(Mesh* mesh)
  : mesh_(mesh),
    local_(Transform::origin()),
    dirty_(true)
  {}

  // Other methods...

private:
  Transform world_;
  bool dirty_;
  // Other fields...
};
```

Now let\'s add two fields, the transform, which calculates the world
transform, and dirty, the dirty flag.

Let\'s add a method to move the node:

```cpp
void GraphNode::setTransform(Transform local) {
  local_ = local;
  dirty_ = true;
}
```

And edit the render method:

```cpp
void GraphNode::render(Transform parentWorld, bool dirty)
{
  dirty |= dirty_;
  if (dirty) {
    world_ = local_.combine(parentWorld);
    dirty_ = false;
  }

  if (mesh_) renderMesh(mesh_, world_);

  for (int i = 0; i < numChildren_; i++) {
    children_[i]->render(world_, dirty);
  }
}
```

This render takes the parentWorld, and a dirty bool. If either are
dirty, we do a recalculation, and set the dirty flag to false. We render
the mesh, and then update all of our children exactly once.

## Design Decisions

## When is the dirty flag cleaned?

- When the result is needed:

Pros:

1.  It avoids calculation entirely if the result is never used.

Cons:

1.  If the calculation is time-consuming, it can cause a noticeable
    pause.

- At well-defined checkpoints:

Pros:

1.  Doing the work doesn\'t impact the user experience

Cons:

1.  You lose control over when the work happens.

- In the background:

Pros:

1.  You can tune how often the work is performed

Cons:

1.  You can do more redundant work.
2.  You need support for asynchronous work.

### How fine-grained is your dirty tracking?

- Fine grained:

1.  You only process data when it changes

- Coarse grained:

1.  You end up processing unchanged data.
2.  Less memory is used for storing dirty flags.
3.  Less time is spent on fixed overhead.

Prev: \[data-locality](data-locality.md) Next:
\[object-pool](object-pool.md)
