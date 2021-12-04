---
title: double-buffer
---

Buffer

# Double Buffer

Cause a series of sequential operations to appear instantaneous or
simultaneous.

A computer must be able to render different frames, one frame at a time.

If we were to paint a frame, and the video driver pulls our frame half
drawn, what ends up happening is half the image renders onto the screen.

Imagine a play, where there is some setup required between scenes. While
the audience is captivated by the play on one stage, the team can prep
for the next scene. When the first scene is done, the audience's
attention is diverted to the second stage, where they can watch the next
scene without any waiting. While that scene plays out, the team preps
the first stage for the next scene.

## When to Use It

1.  We have some state that is being modified incrementally.
2.  That same state may be accessed in the middle of modification.
3.  We want to prevent the code that's accessing the state from seeing
    the work in progress.
4.  We want to be able to read the state and we don't want to have to
    wait while it's being written.

## Keep in Mind

### The swap itself takes time

This pattern requires a swap step that is atomic. No code can access
either state while they are being swapped.

### We have to have two buffers

The other consequence is increased memory usage. You need two copies of
the buffer at any time.

## Sample Code

```cpp
class Scene
{
public:
  Scene() : current_(&buffers_[0]), next_(&buffers_[1]) {}

  void draw() {
    next_->clear();
    next_->draw(1, 1);
    next_->draw(4, 3);
    swap();
  }

  Framebuffer& getBuffer() { return *current_; }

private:
  void swap() {
    // Just switch the pointers.
    Framebuffer* temp = current_;
    current_ = next_;
    next_ = temp;
  }

  Framebuffer  buffers_[2];
  Framebuffer* current_;
  Framebuffer* next_;
};
```

We create a scene class with two buffers, and have them swap buffers. We
always paint to the next buffer, and swap when appropriate.

## How are the buffers swapped?

1.  Swap pointers or references to the buffer:

- It's fast.
- Outside code cannot store persistent pointers to the buffer.

Copy data between the buffers

- Data is kept up to date, as it's only a single frame old.
- Swapping can take more time.

Prev: [state](state.md) Next:
[game-loop](game-loop.md)
