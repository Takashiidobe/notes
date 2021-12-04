---
title: game-loop
---

Loop

# Game Loop

## Intent

Decouple the progression of game time from user input and processor
speed.

## Motivation

The Game Loop is the quintessential game programming pattern; it is used
in games, apps, servers, and operating systems. The Game Loop takes
input from the user and acts on that feedback.

### Interview with a CPU

Early programs used to be batch mode programs, which were programs that
took some data, ran for a bit, and returned a result. Programmers wanted
more immediate feedback, and the first interactive programs (which gave
results immediately) were born.

A game loop might look something like this:

```cpp
while (true) {
  char* command = readCommand();
  handleCommand(command);
}
```

## Event loops

Modern UI applications are very similar to old adventure games. They
look like this, doing nothing until user input.

```cpp
while (true) {
  Event* event = waitForEvent();
  dispatchEvent(event);
}
```

The program is waiting for user input:

```cpp
while (true) {
  processInput();
  update();
  render();
}
```

### A world out of time

This loop has to adjust to the game. How fast does it spin? On fixed
hardware, this was easy, but on newer hardware, there's no guarantee
that any two computers are the same.

### Seconds per second

The game loop runs the game at a consistent speed despite differences in
the underlying hardware.

## The Pattern

A game loop runs continuously during gameplay. It processes user input
without blocking, updates the game state, and renders the game. It
tracks the passage of time to control the rate of gameplay.

## When to Use It

Even if you don't control the game loop of the underlying platform,
you'll be relying on this, so it's good to have an idea of it.

## Keep in mind

Be careful of the way this code performs, since this is the 10% of the
code that has 90% of the impact. Most everything happens inside of the
game loop, so efficiency is king.

### You may need to coordinate with the platform's event loop

In the win32 API, you can use calls like `PeekMessage` to handle and
dispatch events from the OS. Unlike `GetMessage`, `PeekMessage` doesn't
block waiting for user input, so your game loop continues on.

## Sample Code

The code for a game loop is pretty straightforward. Let's talk about
some variations and go over their pros and cons.

Remember that the game loop consists of three parts:

- Processing Input
- Updating State
- Rendering

### Take a little nap

Let's say our game runs at 60FPS, or about 16 ms per frame. For any
other work in between, we'll take a quick nap.

The code might look like this:

```cpp
while (true) {
  double start = getCurrentTime();
  processInput();
  update();
  render();
  sleep(start + MS_PER_FRAME - getcurrentTime()); // sleep for remaining time.
}
```

### One small step, one giant step

Let's try something a bit more sophisticated.

If it takes us more than 16ms to advance the game one frame, the game
loop can't possibly keep up. Let's try to implement a **variable**
time step, which will do this for us.

```cpp
double lastTime = getCurrentTime();
while (true) {
  double current = getCurrentTime();
  double elapsed = current - lastTime;
  processInput();
  update(elapsed);
  render();
  lastTime = current;
}
```

This looks to solve the problem of one game loop, but it doesn't.

Say we've got a two-player networked game, and the two players are
using hardware with different capabilities.

Because one person's computer is better than another's, objects that
are shared between them become unsynchronized. On top of that, floats
have imprecise addition, so they can actually can be subject to rounding
error.

### Play catch up

One part of the engine that usually isn't affected by a variable time
step is rendering. We'll update the game using a fixed time step, but
we'll cause the variable time step to be rendered independently.

```cpp
double previous = getCurrentTime();
double lag = 0.0;
while (true) {
  double current = getCurrentTime();
  double elapsed = current - previous;
  previous = current;
  lag += elapsed;
  processInput();
  while (lag >= MS_PER_UPDATE) {
    update();
    lag -= MS_PER_UPDATE;
  }
  render();
}
```

`MS_PER_UPDATE` is now the granularity we use to update the game. The
shorter this step is, the more processing time it takes to catch up to
real time. We'll want to make this pretty short to make the game look
better to the player. This also frees up a lot of CPU time by removing
rendering from the update loop.

## Design Decisions

At a high level, this is all that's in a game loop. That being said,
there's more to it:

### Do you own the game loop, or does the platform?

- Use the platform's event loop

  - It's simple
  - It plays nice with the platform
  - You lose control over timing

- Use a game engine's loop

  - You don't have to write it
  - You don't get full control

- Write it yourself

  - Total control
  - You have to interface with the platform.

### How do you manage power consumption?

- Run it as fast as you can

  - This works well for PC games.

- Clamp the frame rate:

  - You'll want to set an upper bound of frame rate to be 30-60FPS.
    That way, if all calculations finish, you can sleep for the rest
    of the time, saving battery power.

### How do you control gameplay speed?

- Fixed time step with no synchronization

  - Simple
  - Game speed is affected by hardware

- Fixed time step with synchronization

  - Simple
  - Power friendly
  - The game doesn't play too fast
  - The game can get very slow

- Variable time step

  - It adapts to playing both too slowly and too fast
  - It makes gameplay non-deterministic and unstable

- Fixed update time step, variable rendering

  - It adapts to playing both too slowly and too fast
  - It's more complex

Prev: [double-buffer](double-buffer.md) Next:
[update-method](update-method.md)
