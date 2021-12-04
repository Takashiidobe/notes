---
title: type-object
---

Object

# Type Object

## Intent

Allow the flexible creation of new "classes" by creating a single
class, each instance of which represents a different type of object.

## Motivation

Let's say we want to create monsters for our RPG. We'll start out with
an interface that defines its health and attacks.

```cpp
class Monster {
public:
  virtual ~Monster() {}
  virtual const char* getAttack() = 0;
protected:
  Monster(int startingHealth) : health_(startingHealth) {}
private:
  int health_;
};
```

And some implementations:

```cpp
class Dragon : public Monster {
public:
  Dragon() : Monster(230) {}

  virtual const char* getAttack() {
    return "The dragon breathes fire!";
  }
};

class Troll : public Monster {
public:
  Troll() : Monster(48) {}

  virtual const char* getAttack() {
    return "The troll clubs you!";
  }
};
```

Eventually, when we want to have hundreds of different monsters, compile
times become extremely slow and our designers and devs are frustrated.
We take an email, create the class the designer wants, and recompile the
code. We become data monkeys. We want to make this more available at
runtime.

## A class for a class

We normally think in an OOP fashion, with polymorphism. Thus, our
hierarchy looks like this:

                Dragon
    Monster <- |
                Troll

When this branches out to hundreds of classes, this leads to a large
class hierarchy.

Instead, we can architect our code so that each monster has a breed.

    Monster <- Breed

There's no inheritance at all. The `Breed` class that we create
contains the information that's shared between all monsters. The breed
is essentially the type of the monster.

## The Pattern

Define a type object class and a typed object class. Each type object
instance represents a different logical type. Each typed object stores a
reference to the type object that describes its type.

## When to Use it

- You don't know what types you will need up front
- You want to be able to modify or add new types without having to
  recompile or change code

## Keep in Mind

- This pattern makes types more flexible by hoisting your types to
  data, but it makes it less strict.

### The type objects have to be tracked manually

Instead of using vtables set up by C++, we'll have to manually track
the vtables ourselves.

### It's harder to define behavior for each type

With subclassing, we can override a method and do whatever you want to.
With the type object pattern, we replace an overridden method with a
member variable. This makes it easy to use type-specific data, but hard
to define type-specific behavior.

## Sample Code

Here's the breed class:

```cpp
class Breed {
public:
  Breed(int health, const char* attack)
  : health_(health),
    attack_(attack)
  {}

  int getHealth() { return health_; }
  const char* getAttack() { return attack_; }

private:
  int health_; // Starting health.
  const char* attack_;
};
```

Here's the monster class:

```cpp
class Monster {
public:
  Monster(Breed& breed)
  : health_(breed.getHealth()),
    breed_(breed)
  {}

  const char* getAttack() {
    return breed_.getAttack();
  }

private:
  int    health_; // Current health.
  Breed& breed_;
};
```

Each monster takes a breed in its constructor and holds a reference to
it.

### Making type objects more like types: constructors

We have to construct a monster directly and pass in its breed. This is a
little backwards:

Let's make our constructor do this for us.

```cpp
class Breed
{
public:
  Monster* newMonster() { return new Monster(*this); }

  // Previous Breed code...
};
```

And the Monster class:

```cpp
class Monster {
  friend class Breed;

public:
  const char* getAttack() { return breed_.getAttack(); }

private:
  Monster(Breed& breed)
  : health_(breed.getHealth()),
    breed_(breed)
  {}

  int health_; // Current health.
  Breed& breed_;
};
```

By making the monster's constructor private, it can only be called by
friend classes (of which our breed is). Thus, our breed can call the
function directly in its constructor.

### Sharing data through inheritance:

We'll support single inheritance, allowing a class to have a parent
base class.

```cpp
class Breed {
public:
  Breed(Breed* parent, int health, const char* attack)
  : parent_(parent),
    health_(health),
    attack_(attack)
  {}

  int         getHealth();
  const char* getAttack();

private:
  Breed*      parent_;
  int         health_; // Starting health.
  const char* attack_;
};
```

When we want to construct a breed without parents, we can pass in `NULL`
for a base breed that has no ancestors.

We can also handle which attributes are inherited either dynamically or
at construction.

Dynamically:

```cpp
int Breed::getHealth() {
  // Override.
  if (health_ != 0 || parent_ == NULL) return health_;

  // Inherit.
  return parent_->getHealth();
}

const char* Breed::getAttack() {
  // Override.
  if (attack_ != NULL || parent_ == NULL) return attack_;

  // Inherit.
  return parent_->getAttack();
}
```

At construction time (if overridden attributes don't change):

```cpp
Breed(Breed* parent, int health, const char* attack)
: health_(health),
  attack_(attack) {
  // Inherit non-overridden attributes.
  if (parent != NULL) {
    if (health == 0) health_ = parent->getHealth();
    if (attack == NULL) attack_ = parent->getAttack();
  }
}
```

To actually implement the data, let's say we use a JSON file:

```json
{
  "Troll": {
    "health": 25,
    "attack": "The troll hits you!"
  },
  "Troll Archer": {
    "parent": "Troll",
    "health": 0,
    "attack": "The troll archer fires an arrow!"
  },
  "Troll Wizard": {
    "parent": "Troll",
    "health": 0,
    "attack": "The troll wizard casts a spell on you!"
  }
}
```

This way, Troll Archer and Troll Wizard inherit from troll, but they
have different attacks.

This is much like the [prototype](prototype.md) pattern.

Prev: [subclass-sandbox](subclass-sandbox.md)
Next: [component](component.md)
