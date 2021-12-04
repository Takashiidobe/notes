---
title: event-queue
---

Queue

# Event Queue

## Intent

Decouple when a message or event is sent from when it is processed.

## GUI event loops

Every time the user interacts with your program, the operating system
generates an event. It then allows you to process these events.

```cpp
while (running) {
    Event event = getNextEvent();
    // handle event
}
```

Your app takes these events and processes them somehow.

## Central Event bus

Let's say we want to implement a tutorial system. The player slays two
cows, and they get an achievement.

Instead of coupling tutorial code into your combat system, you may want
to use an event queue.

This allows any system to send events to the game queue, and any system
to receive events from the game queue.

## Example

Let's say we want to create sounds when monsters are slain.

```cpp
class Audio {
public:
    static void playSound(SoundId id, int volume);
};
```

```cpp
void Audio::playSound(SoundId id, int volume) {
  ResourceId resource = loadSound(id);
  int channel = findOpenChannel();
  if (channel == -1) return;
  startSound(resource, channel, volume);
}
```

Then we play said sound:

```cpp
class Menu {
public:
    void onSelect(int index) {
        Audio::playSound(SOUND_BLOOP, VOL_MAX);
    }
};
```

We have a few problems, though:

### Problem 1: The API blocks

- This API call is synchronous, which means it'll freeze the game
  while trying to fetch the sound from disk.

### Problem 2: Requests cannot be processed in aggregate

- This code has no synchronization, which means it's not thread safe,
  and also blocks other threads, if they want to call this code at the
  same time too.

### Problem 3: Requests are processed on the wrong thread.

- This forces the current thread to drop what it's doing and play the
  sound now.

### The Pattern

This pattern decouples the sender from the receiver both statically and
in time.

If you just want to decouple who receives a message from its sender, use
the [observer](observer.md) or
[command](command.md) patterns.

### Keep in Mind

### A central event queue is a global variable

- It's nicely wrapped up, but it's still a global variable. Try to
  limit its use to only the systems that need to know about it.

### The state of the world can change under you

- You'll have to send your payload with all of the state that you
  need of the event.
- If you want to tie the amount of exp points the main character gets
  with the HP of the monster, the monster may be deallocated by the
  time the exp system gets its message. Make sure your messages have
  all the information they need to process.

Try to avoid sending events from within code that's handling an event.

### Sample Code

```cpp
struct PlayMessage {
  SoundId id;
  int volume;
};
```

```cpp
class Audio {
public:
  static void init() {
    numPending_ = 0;
  }

  // Other stuff...
private:
  static const int MAX_PENDING = 16;

  static PlayMessage pending_[MAX_PENDING];
  static int numPending_;
};
```

Then we play the sound:

```cpp
void Audio::playSound(SoundId id, int volume) {
  assert(numPending_ < MAX_PENDING);

  pending_[numPending_].id = id;
  pending_[numPending_].volume = volume;
  numPending_++;
}
```

```cpp
class Audio {
public:
  static void update() {
    for (int i = 0; i < numPending_; i++) {
      ResourceId resource = loadSound(pending_[i].id);
      int channel = findOpenChannel();
      if (channel == -1) return;
      startSound(resource, channel, pending_[i].volume);
    }
    numPending_ = 0;
  }
};
```

We can do better with a ring buffer, or circular array:

First, make two markers to the head:

```cpp
class Audio {
public:
  static void init() {
    head_ = 0;
    tail_ = 0;
  }

  // Methods...
private:
  static int head_;
  static int tail_;

  // Array...
};
```

Now we add to the end of the list:

```cpp
void Audio::playSound(SoundId id, int volume) {
  assert(tail_ < MAX_PENDING);

  // Add to the end of the list.
  pending_[tail_].id = id;
  pending_[tail_].volume = volume;
  tail_++;
}
```

Then we use `update()` to increment the head pointer as needed:

```cpp
void Audio::update() {
  // If there are no pending requests, do nothing.
  if (head_ == tail_) return;

  ResourceId resource = loadSound(pending_[head_].id);
  int channel = findOpenChannel();
  if (channel == -1) return;
  startSound(resource, channel, pending_[head_].volume);

  head_++;
}
```

Now we loop around:

```cpp
void Audio::playSound(SoundId id, int volume) {
  assert((tail_ + 1) % MAX_PENDING != head_);

  // Add to the end of the list.
  pending_[tail_].id = id;
  pending_[tail_].volume = volume;
  tail_ = (tail_ + 1) % MAX_PENDING;
}
```

```cpp
void Audio::update() {
  // If there are no pending requests, do nothing.
  if (head_ == tail_) return;

  ResourceId resource = loadSound(pending_[head_].id);
  int channel = findOpenChannel();
  if (channel == -1) return;
  startSound(resource, channel, pending_[head_].volume);

  head_ = (head_ + 1) % MAX_PENDING;
}
```

We can now aggregate requests in `O(n)` time by merging requests with
the same soundId.

```cpp
void Audio::playSound(SoundId id, int volume) {
  // Walk the pending requests.
  for (int i = head_; i != tail_;
       i = (i + 1) % MAX_PENDING) {
    if (pending_[i].id == id) {
      // Use the larger of the two volumes.
      pending_[i].volume = max(volume, pending_[i].volume);

      // Don't need to enqueue.
      return;
    }
  }
  // Previous code...
}
```

Prev: [component](component.md) Next:
[service-locator](service-locator.md)
