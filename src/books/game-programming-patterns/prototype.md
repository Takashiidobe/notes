---
title: prototype
---

# Prototype

Let's pretend we have a lot of monsters.

```cpp
class Monster {/* implementation */};

class Ghost : public Monster {};
class Demon : public Monster {};
class Sorcerer : public Monster {};
```

A Spawner would create a monster type:

```cpp
class Spawner {
  public:
    virtual ~Spawner() {}
    virtual Monster* spawnMonster() = 0;
};

class GhostSpawner : public Spawner {
  public:
    virtual Monster* spawnMonster() {
      return new Ghost();
    }
};

class DemonSpawner : public Spawner {
  public:
    virtual Monster* spawnMonster() {
      return nenw Demon();
    }
};
```

This has a lot of repetition. Instead, using the prototypes pattern, we
allow objects to spawn objects similar to itself.

Let's give our base class an abstract `clone()` method.

```cpp
class Monster {
  public:
    virtual ~Monster() {}
    virtual Monster* clone() = 0;
};
```

Each monster then provides an implementation that returns a new object
identical to itself.

```cpp
class Ghost : public Monster {
  public:
    Ghost(int health, int speed) : health_(health), speed_(speed) {}
    virtual Monster* clone() { return new Ghost(health_, speed_); }
  private:
    int health_;
    int speed_;
};
```

Now, we no longer need a spawner class for each monster.

```cpp
class Spawner {
  public:
    Spawner(Monster* prototype) : prototype_(prototype) {}

    Monster* spawnMonster() { return prototype_->clone(); }
  private:
    Monster* prototype_;
};
```

Every spawner now has a monster embedded in it which it clones.

```cpp
Monster* ghostPrototype = new Ghost(15, 3);
Spawner* ghostSpawner = new Spawner(ghostPrototype);
Ghost* ghost = ghostSpawner.clone(); // returns a ghost with 15 health and 3 speed.
```

## Spawn Functions

As an alternative, we can create spawn functions:

```cpp
Monster* spawnGhost() {
  return new Ghost();
}
```

The spawner class can store a function pointer instead:

```cpp
typedef Monster* (*SpawnCallback)();
class Spawner {
public:
  Spawner(SpawnCallback spawn)
  : spawn_(spawn)
  {}

  Monster* spawnMonster() {
    return spawn_();
  }

private:
  SpawnCallback spawn_;
};
```

And then to create a spawner for ghosts:

```cpp
Spawner* ghostSpawner = new Spawner(spawnGhost);
```

We can use templates too:

```cpp
class Spawner {
public:
  virtual ~Spawner() {}
  virtual Monster* spawnMonster() = 0;
};

template <class T>
class SpawnerFor : public Spawner  {
public:
  virtual Monster* spawnMonster() { return new T(); }
};
```

To create a ghost:

```cpp
Spawner* ghostSpawner = new SpawnerFor<Ghost>();
```

## The Prototype Language Paradigm

- Prototypical languages are OOP. Javascript is a good example

Normally, class based languages have methods contained in the class, and
state in the instance.

Class Instance

---

Method Field
Method Field
Method Field

### Self

- In a Prototypical language like self, an object contains both state
  and behavior.

Object

---

Field
Method
Field

To implement inheritance in Self, self allows you to designate parents:
If you find a field or method on an object, you stop there. If not, you
look at its parent(s).

To create a new object, you change its state and then call clone on it
to create a new state.

## Prototypes for Data Modeling

Games shuffle a lot of state to and from places. Wouldn't it be nice if
we could have more dynamic behavior?

Let's say we separate our state from our game by using JSON.

Let's define a goblin.

```json
{
  "name": "goblin grunt",
  "minHealth": 20,
  "maxHealth": 30,
  "resists": ["cold", "poison"],
  "weaknesses": ["fire", "light"]
}
```

Let's make more goblins.

```json
[
  {
    "name": "goblin wizard",
    "minHealth": 20,
    "maxHealth": 30,
    "resists": ["cold", "poison"],
    "weaknesses": ["fire", "light"],
    "spells": ["fire ball", "lightning bolt"]
  },
  {
    "name": "goblin archer",
    "minHealth": 20,
    "maxHealth": 30,
    "resists": ["cold", "poison"],
    "weaknesses": ["fire", "light"],
    "attacks": ["short bow"]
  }
]
```

This has a lot of duplication. Not great, since it means we have to
change more code if we want to change things, and isn't everything just
a goblin?

```json
[
  {
    "name": "goblin grunt",
    "minHealth": 20,
    "maxHealth": 30,
    "resists": ["cold", "poison"],
    "weaknesses": ["fire", "light"]
  },
  {
    "name": "goblin wizard",
    "prototype": "goblin grunt",
    "spells": ["fire ball", "lightning bolt"]
  },
  {
    "name": "goblin archer",
    "prototype": "goblin grunt",
    "attacks": ["short bow"]
  }
]
```

Now, we can remove duplication and have each goblin archer have a goblin
grunt inside of it that it takes from, and then applies changes to.

Prev: [observer](observer.md) Next:
[singleton](singleton.md)
