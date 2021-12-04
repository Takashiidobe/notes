---
title: subclass-sandbox
---

Sandbox

# Subclass Sandbox

## Intent

Define behavior in a subclass using a set of operations provided by its
base class.

## Motivation

Let\'s say we want to create a class template that implements all
superpowers. Here are some cons:

1.  Redundant Code
2.  Tight Coupling
3.  Code Breakage
4.  Hard to define Invariants

We can create a base class called `Superpower` that has **protected**
non-virtual methods to communicate that they are meant to be called by
subclasses.

This is the Subclass Sandbox Pattern, which has a wide and shallow class
hierarchy.

## The Pattern

A base class defines an abstract sandbox method and several provided
operations. Marking them protected makes it clear that they are for use
by derived classes. Each derived sandboxed subclass implements the
sandbox method using the provided operations.

## When to Use it

1.  There is a base class with lots of derived classes
2.  The base class is able to provide all the operations that a derived
    class may need to perform
3.  There is behavioral overlap in the subclasses
4.  You want to minimize coupling

## Keep in Mind

Inheritance isn\'t thought of kindly because base classes tend to
accumulate lots of code.

With this pattern, since every subclass goes through its base class to
reach the rest of the game, you can end up with the brittle base class
problem.

If you get spaghetti code from this pattern, try turning to the
\[component](component.md) pattern.

## Sample Code

Let\'s make the Superpower base class:

```cpp
class Superpower {
public:
  virtual ~Superpower() {}

protected:
  virtual void activate() = 0;

  void move(double x, double y, double z) {
    // Code here...
  }

  void playSound(SoundId sound, double volume) {
    // Code here...
  }

  void spawnParticles(ParticleType type, int count) {
    // Code here...
  }
};
```

The active method is protected and abstract, which signals that
subclasses must override it.

The other protected methods are the provided operations. These methods
will be called in `activate`.

Making a superpower goes like this:

```cpp
class SkyLaunch : public Superpower {
protected:
  virtual void activate() {
    playSound(SOUND_SPROING, 1.0f);
    spawnParticles(PARTICLE_DUST, 10);
    move(0, 0, 20);
  }
};
```

Let\'s say we want to add some control flow based on the hero\'s
location. We can add that to the Superpower:

```cpp
class Superpower {
protected:
  double getHeroX() {
    // Code here...
  }

  double getHeroY() {
    // Code here...
  }

  double getHeroZ() {
    // Code here...
  }

  // Existing stuff...
};
```

Now that we can access state, we can make some interesting stuff happen:

```cpp
class SkyLaunch : public Superpower {
protected:
  virtual void activate() {
    if (getHeroZ() == 0) {
      // On the ground, so spring into the air.
      playSound(SOUND_SPROING, 1.0f);
      spawnParticles(PARTICLE_DUST, 10);
      move(0, 0, 20);
    }
    else if (getHeroZ() < 10.0f) {
      // Near the ground, so do a double jump.
      playSound(SOUND_SWOOP, 1.0f);
      move(0, 0, getHeroZ() + 20);
    }
    else {
      // Way up in the air, so do a dive attack.
      playSound(SOUND_DIVE, 0.7f);
      spawnParticles(PARTICLE_SPARKLES, 1);
      move(0, 0, -getHeroZ());
    }
  }
};
```

## Design Decisions

This is a fairly small pattern that has a lot of flexibility.

### What operations should be provided?

- Should we add methods to the base class?

  - If a lot of derived classes use it, sure, otherwise leave it in
    derived classes.

- Should calls modify state?

  - You should avoid modifying state, because that can introduce
    coupling across the codebase.

### Should methods be provided directly, or through objects that contain them?

Let\'s say that we want to add more methods to the base class to play
music:

```cpp
class Superpower {
protected:
  void playSound(SoundId sound, double volume) {
    // Code here...
  }

  void stopSound(SoundId sound) {
    // Code here...
  }

  void setVolume(SoundId sound) {
    // Code here...
  }

  // Sandbox method and other operations...
};
```

Instead of adding it directly to the Superpower class, why don\'t we
create a new class that encapsulates it:

```cpp
class SoundPlayer {
  void playSound(SoundId sound, double volume) {
    // Code here...
  }

  void stopSound(SoundId sound) {
    // Code here...
  }

  void setVolume(SoundId sound) {
    // Code here...
  }
};
```

And have the Superpower manage access to it.

```cpp
class Superpower {
protected:
  SoundPlayer& getSoundPlayer() {
    return soundPlayer_;
  }

  // Sandbox method and other operations...

private:
  SoundPlayer soundPlayer_;
};
```

### How does the base class get the state that it needs?

- Pass it to the base constructor

This is the simplest way:

```cpp
class Superpower {
public:
  Superpower(ParticleSystem* particles)
  : particles_(particles)
  {}

  // Sandbox method and other operations...

private:
  ParticleSystem* particles_;
};
```

But now all derived classes will need a constructor that calls the base
class one and passes along that argument. This is a maintenance
headache.

```cpp
class SkyLaunch : public Superpower {
public:
  SkyLaunch(ParticleSystem* particles)
  : Superpower(particles)
  {}
};
```

- Do two-stage initialization:

To avoid passing everything through the constructor, we can split
initialization into two steps:

```cpp
Superpower* power = new SkyLaunch();
power->init(particles);
```

This lets us initialize the superpower base class and the derived class
at different times. Let\'s create a helper function so we don\'t forget
to initialize both at the same time.

```cpp
Superpower* createSkyLaunch(ParticleSystem* particles) {
  Superpower* power = new SkyLaunch();
  power->init(particles);
  return power;
}
```

- Make the state static:

If some systems required are singletons, we can make initialization
static:

```cpp
class Superpower {
public:
  static void init(ParticleSystem* particles) {
    particles_ = particles;
  }

  // Sandbox method and other operations...

private:
  static ParticleSystem* particles_;
};
```

This makes it so every instance of Superpower doesn\'t have to store its
own instance of particles, so this uses up less memory. Of course,
we\'ll need to call `Superpower::init()` before we can use it.

- Use a \[service-locator](service-locator.md)

```cpp
class Superpower {
protected:
  void spawnParticles(ParticleType type, int count) {
    ParticleSystem& particles = Locator::getParticles();
    particles.spawn(type, count);
  }

  // Sandbox method and other operations...
};
```

Prev: \[bytecode](bytecode.md) Next:
\[type-object](type-object.md)
