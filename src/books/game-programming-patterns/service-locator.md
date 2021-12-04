---
title: service-locator
---

Locator

# Service Locator

## Intent

Provide a global point of access to a service without coupling users to
the concrete class that implements it.

There are many classes that are used frequently throughout the codebase,
like allocators, logging, or random number generation.

Let's talk about playing sounds:

Should we use a static class?

```cpp
AudioSystem::playSound(VERY_LOUD_BANG);
```

Or a singleton?

```cpp
AudioSystem::instance()->playSound(VERY_LOUD_BANG);
```

Either way does the job, but we introducing coupling. And if we decide
to refactor it, we have to change every caller.

There's a better solution: a phone book.

People that need to get in touch with us can look us up by name and get
our current address. When we move, we tell the phone company. They
update the book, and everyone gets the new address. We don't need our
own address at all.

This is the Service locator pattern: it decouples code that needs a
service from **who** it is (concrete implementation) and **where** it is
(how we get to the instance of it).

## The Pattern

A service class defines an abstract interface to a set of operations. A
concrete service provider implements this interface. A separate service
locator provides access to the service by finding an appropriate
provider while hiding both the provider's concrete type and the process
used to locate it.

## When to use it

This is still global state like the singleton. Use it sparingly.

If you can, consider passing the object to it instead.

But, if you can't, this pattern works.

## Keep in Mind

The service locator defers coupling between two pieces of code until
runtime. This gives you flexibility, but the price you pay is it's
harder to understand what your dependencies are by reading the code.

### The service actually has to be located

Since this pattern has to locate the service, we have to handle the case
where that fails. We'll need a null service for that.

### The service doesn't know who is locating it

Since the locator is globally accessible, any code in the game could be
requesting a service and then poking at it. If a service can only be
used in certain contexts, it's best not to expose it to the world with
this pattern.

## Sample Code

### The service

Here's the interface for the service:

```cpp
class Audio {
public:
  virtual ~Audio() {}
  virtual void playSound(int soundID) = 0;
  virtual void stopSound(int soundID) = 0;
  virtual void stopAllSounds() = 0;
};
```

### The service provider

Here's an implementation:

```cpp
class ConsoleAudio : public Audio {
public:
  virtual void playSound(int soundID) {
    // Play sound using console audio api...
  }

  virtual void stopSound(int soundID) {
    // Stop sound using console audio api...
  }

  virtual void stopAllSounds() {
    // Stop all sounds using console audio api...
  }
};
```

### A simple locator

And the locator:

```cpp
class Locator {
public:
  static Audio* getAudio() { return service_; }

  static void provide(Audio* service) {
    service_ = service;
  }

private:
  static Audio* service_;
};
```

This is dependency injection: if you have one class that depends on
another, outside code is responsible for injecting that dependency into
the object that needs it.

the static function `getAudio()` does the locating. Call it to get an
instance back of the service.

```cpp
Audio *audio = Locator::getAudio();
audio->playSound(VERY_LOUD_BANG);
```

The way it is located is simple. It relies on outside code to register a
service provider: When the game is starting up, it calls some code like
this:

```cpp
ConsoleAudio *audio = new ConsoleAudio();
Locator::provide(audio);
```

This class takes the interface, not a concrete implementation, so it
doesn't need to know about it's implementation, which lets it be
applied retroactively to existing classes.

## A null service

Our implementation is simple and flexible so far. If we try to use the
service before a provider has been registered, it returns `NULL`. If the
calling code doesn't check that, we're going to crash the game.

Let's provide a Null Object to address this. The null object is an
implementation that does nothing.

```cpp
class NullAudio: public Audio {
public:
  virtual void playSound(int soundID) { /* Do nothing. */ }
  virtual void stopSound(int soundID) { /* Do nothing. */ }
  virtual void stopAllSounds()        { /* Do nothing. */ }
};
```

Now we need our locator to handle this:

```cpp
class Locator {
public:
  static void initialize() { service_ = &nullService_; }

  static Audio& getAudio() { return *service_; }

  static void provide(Audio* service) {
    if (service == NULL) {
      // Revert to null service.
      service_ = &nullService_;
    }
    else {
      service_ = service;
    }
  }

private:
  static Audio* service_;
  static NullAudio nullService_;
};
```

We're defaulting our service to an instance of nullService, and
returning a reference, which is an indication this can't be null.

## Logging decorator

Let's discuss another refinement to this pattern: Decorated services.

Let's try to decorate our audio class by wrapping it with a logging
function.

```cpp
class LoggedAudio : public Audio {
public:
  LoggedAudio(Audio &wrapped)
  : wrapped_(wrapped)
  {}

  virtual void playSound(int soundID) {
    log(;
    wrapped_.playSound(soundID);
  }

  virtual void stopSound(int soundID) {
    log(;
    wrapped_.stopSound(soundID);
  }

  virtual void stopAllSounds() {
    log(;
    wrapped_.stopAllSounds();
  }

private:
  void log(const char* message) {
    // Code to log message...
  }

  Audio &wrapped_;
};
```

Now to enable audiologging, here's what we do:

```cpp
// Decorate the existing service.
Audio *service = new LoggedAudio(Locator::getAudio());

// Swap it in.
Locator::provide(service);
```

## Design Decisions

### How is the service located?

- Outside code registers it:

This is what we did, and it's the most common:

Pros:

1.  It's fast and simple:
2.  We control construction:
3.  We can change the service while the game is running

Cons:

1.  The locator depends on outside code. If the locator isn't
    initialized properly, it'll crash mysteriously.

- Bind it at compile time:

Using preprocessor macros:

```cpp
class Locator {
public:
  static Audio& getAudio() { return service_; }

private:
  #if DEBUG
    static DebugAudio service_;
  #else
    static ReleaseAudio service_;
  #endif
};
```

Pros:

1.  It's fast
2.  the service is always available

Cons:

3.  You can't change the service without recompiling

- Configure it at runtime:

This is what most people do in enterprise business software:

We can put everything in a configuration file that's loaded at runtime.

Pros:

1.  We can swap out the service without recompiling
2.  Non-programmers can change the service
3.  The same codebase can support multiple configurations simultaneously

Cons:

1.  It's complex: you need some way to store and load the
    configurations
2.  It's very slow.

### What happens if the service can't be located?

- Let the user handle it:

If the locator can't find the service, return `NULL`:

1.  It lets users determine how to handle failure.
2.  Users of the service must handle the failure.

- Halt the game:

Assert the service exists. If not, crash the game.

```cpp
class Locator {
public:
  static Audio& getAudio() {
    Audio* service = NULL;

    // Code here to locate service...

    assert(service != NULL);
    return *service;
  }
};
```

1.  Users don't need to handle a missing service
2.  The game will crash if not found.

- Return a null service:

1.  User's don't need to handle a missing service
2.  The game will continue if the service isn't available
3.  It is harder to debug

## What is the scope of the service?

Up till now, anyone can get the service through the locator. We can
limit access to a single class and its descendants:

```cpp
class Base {
  // Code to locate service and set service_...

protected:
  // Derived classes can use service
  static Audio& getAudio() { return *service_; }

private:
  static Audio* service_;
};
```

Access to the service is restricted to classes that inherit Base: that
way, we control coupling. This can be useful for services that need to
be scoped.

Prev: [event-queue](event-queue.md) Next:
[data-locality](data-locality.md)
