---
title: component
---

# Component

## Intent

Allow a single entity to span multiple domains without coupling the
domains to each other.

## The Pattern

Imagine we have a class that spans multiple domains. We could have a
single class manage all of the complexity, or we could split each domain
into its own class, and have our class just manage the components.

## When to Use It

- You have a class that touches multiple domains which you want to
  keep decoupled from each other.

- A class is getting massive and hard to work with.

- You want to be able to define a variety of objects that share
  different capabilities, but using inheritance doesn't let you pick
  the parts you want to reuse precisely enough.

## Splitting out a Domain

```cpp
class Bjorn {
public:
    Bjorn() : velocity_(0), x_(0), y_(0) {}

    void update(World& world, Graphics& graphics);
private:
    static const int WALK_ACCELERATION = 1;

    int velocity_;
    int x_;
    int y_;
    Volume volume_;
    Sprite spriteStand_;
    Sprite spriteWalkLeft_;
    Sprite spriteWalkRight_;
};
```

```cpp
void Bjorn::update(World& world, Graphics& graphics) {
    switch (Controller::getJoystickDirection()) {
        case DIR_LEFT:
            velocity_ -= WALK_ACCELERATION;
            break;
        case DIR_RIGHT:
            velocity_ += WALK_ACCELERATION;
            break;
    }

    x_ += velocity_;
    world.resolveCollision(volume_, x_, y_, velocity_);
    Sprite* sprite = &spriteStand_;
    if (velocity < 0) sprite = &spriteWalkLeft_;
    else if (velocity_ > 0) sprite = &spriteWalkRight_;

    graphics.draw(*sprite, x_, y);
}
```

### Splitting Out a Domain

```cpp
class InputComponent {
public:
    void update(Bjorn& bjorn) {
        switch (Controller::getJoystickDirection()) {
            case DIR_LEFT:
                bjorn.velocity -= WALK_ACCELERATION;
                break;
            case DIR_RIGHT:
                bjorn.velocity += WALK_ACCELERATION;
                break;
        }
    }
private:
    static const int WALK_ACCELERATION = 1;
};
```

```cpp
class Bjorn {
public:
    int velocity;
    int x;
    int y;

    void update(World& world, Graphics& graphics) {
        input_.update(*this);

        x += velocity;
        world.resolveCollision(volume_, x, y, velocity);

        Sprite* sprite = &spriteStand_;
        updateSprite(*sprite);
        graphics.draw(*sprite, bjorn.x, bjorn.y)
    }
private:
    void updateSprite(Sprite& sprite) {
        if (velocity < 0) sprite = &spriteWalkLeft_;
        else if (velocity > 0) sprite = &spriteWalkRight_;
    }
    InputComponent input_;
    Volume volume_;

    Sprite spriteStand_;
    Sprite SpriteWalkLeft_;
    Sprite spriteWalkRight_;
};
```

Let's keep splitting:

```cpp
class PhysicsComponent
{
public:
  void update(Bjorn& bjorn, World& world)
  {
    bjorn.x += bjorn.velocity;
    world.resolveCollision(volume_,
        bjorn.x, bjorn.y, bjorn.velocity);
  }

private:
  Volume volume_;
};
```

```cpp
class GraphicsComponent
{
public:
  void update(Bjorn& bjorn, Graphics& graphics)
  {
    Sprite* sprite = &spriteStand_;
    if (bjorn.velocity < 0)
    {
      sprite = &spriteWalkLeft_;
    }
    else if (bjorn.velocity > 0)
    {
      sprite = &spriteWalkRight_;
    }

    graphics.draw(*sprite, bjorn.x, bjorn.y);
  }

private:
  Sprite spriteStand_;
  Sprite spriteWalkLeft_;
  Sprite spriteWalkRight_;
};
```

Here's our Bjorn Class.

```cpp
class Bjorn
{
public:
  int velocity;
  int x, y;

  void update(World& world, Graphics& graphics)
  {
    input_.update(*this);
    physics_.update(*this, world);
    graphics_.update(*this, graphics);
  }

private:
  InputComponent input_;
  PhysicsComponent physics_;
  GraphicsComponent graphics_;
};
```

### Robo Bjorn

One more step, we can make this better by abstracting out the behavior
to interfaces.

```cpp
class InputComponent {
public:
    virtual ~Inputcomponent() {}
    virtual void update(Bjorn& bjorn) = 0;
};
```

Next, we have our current user input handling code conform to that
interface:

```cpp
class PlayerInputComponent: public InputComponent {
public:
  virtual void update(Bjorn& bjorn) {
    switch (Controller::getJoystickDirection()) {
      case DIR_LEFT:
        bjorn.velocity -= WALK_ACCELERATION;
        break;

      case DIR_RIGHT:
        bjorn.velocity += WALK_ACCELERATION;
        break;
    }
  }

private:
  static const int WALK_ACCELERATION = 1;
};
```

Now Bjorn should hold a pointer to that input component instead of
having an inline instance:

```cpp
class Bjorn {
public:
  int velocity;
  int x, y;

  Bjorn(InputComponent* input)
  : input_(input)
  {}

  void update(World& world, Graphics& graphics) {
    input_->update(*this);
    physics_.update(*this, world);
    graphics_.update(*this, graphics);
  }

private:
  InputComponent* input_;
  PhysicsComponent physics_;
  GraphicsComponent graphics_;
};
```

Now, when we instantiate Bjorn, we pass in an input component for it.

```cpp
Bjorn* bjorn = new Bjorn(new PlayerInputComponent());
```

We pay the cost of a virtual function call for our `update()` functions,
but instead, we can swap out the `InputComponent` at will:

Let's say we wanted an AI to control Bjorn, like on a Demo screen:

```cpp
class DemoInputComponent: public InputComponent {
public:
    virtual void update(Bjorn& bjorn) {
        // Allow AI to control Bjorn
    }
};
```

Now we wire him up with our new component:

```cpp
Bjorn* bjorn = new Bjorn(new DemoInputComponent());
```

### No Bjorn at all?

Actually, Bjorn is just a component bag. Let's go further with the
physics and graphics and make them interfaces too.

```cpp
class PhysicsComponent {
public:
  virtual ~PhysicsComponent() {}
  virtual void update(GameObject& obj, World& world) = 0;
};

class GraphicsComponent {
public:
  virtual ~GraphicsComponent() {}
  virtual void update(GameObject& obj, Graphics& graphics) = 0;
};
```

Rename Bjorn as GameObject:

```cpp
class GameObject {
public:
  int velocity;
  int x, y;

  GameObject(InputComponent* input,
             PhysicsComponent* physics,
             GraphicsComponent* graphics)
  : input_(input),
    physics_(physics),
    graphics_(graphics)
  {}

  void update(World& world, Graphics& graphics) {
    input_->update(*this);
    physics_->update(*this, world);
    graphics_->update(*this, graphics);
  }

private:
  InputComponent* input_;
  PhysicsComponent* physics_;
  GraphicsComponent* graphics_;
};
```

```cpp
class BjornPhysicsComponent : public PhysicsComponent {
public:
  virtual void update(GameObject& obj, World& world) {
    // Physics code...
  }
};

class BjornGraphicsComponent : public GraphicsComponent {
public:
  virtual void update(GameObject& obj, Graphics& graphics) {
    // Graphics code...
  }
};
```

And now we can build Bjorn again, without even having a dedicated class
for him.

```cpp
GameObject* createBjorn() {
  return new GameObject(new PlayerInputComponent(),
                        new BjornPhysicsComponent(),
                        new BjornGraphicsComponent());
}
```

### How does the object get its components?

- If the object creates its own components:
  - The object itself ensures it has the components it needs.
  - It's harder to reconfigure the object.
- If outside code provides the components:
  - The object becomes flexible
  - It can be decoupled from the concrete component types.

### How do components communicate?

- By modifying the container object's state.
- By referring directly to each other.
- By sending messages There's no one right answer

Prev: [type-object](type-object.md) Next:
[event-queue](event-queue.md)
