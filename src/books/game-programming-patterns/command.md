---
title: command
---

# Command

A command is an object-oriented replacement for callbacks.

## Configuring Input

- Let's say we have to configure input:

```cpp
enum class Button { X, Y, A, B };
class InputHandler {};

void InputHandler::handleInput() {
    if (isPressed(BUTTON::X)) jump();
    else if (isPressed(BUTTON::Y)) fireGun();
    else if (isPressed(BUTTON::A)) swapWeapon();
    else if (isPressed(BUTTON::B)) lurchIneffectively();
}
```

Most games allow their buttons to be re-mapped, so this won't work.
We'll need to find a way to swap out the action that occurs when a
button is is pressed.

Define a base class that allows for this:

```cpp
class Command {
    public:
        virtual ~Command() {}
        virtual void execute() = 0;
};
```

Create subclasses for each action:

```cpp
class JumpCommand : public Command {
    public:
        void execute() override { jump(); }
};
class FireCommand : public Command {
    public:
        void execute() override { fireGun(); }
};
```

In the input handler, store a pointer to a command for each button:

```cpp
class InputHandler {
    public:
        void handleInput();
        void bindToX(Command& c) { buttonX_ = c; }
        void bindToY(Command& c) { buttonY_ = c; }
        void bindToA(Command& c) { buttonA_ = c; }
        void bindToB(Command& c) { buttonB_ = c; }
    private:
        Command* buttonX_;
        Command* buttonY_;
        Command* buttonA_;
        Command* buttonB_;
};
```

Now the input handler can delegate to the command.

```cpp
void InputHandler::handleInput() {
  if (isPressed(BUTTON::X)) buttonX_->execute();
  else if (isPressed(BUTTON::Y)) buttonY_->execute();
  else if (isPressed(BUTTON::A)) buttonA_->execute();
  else if (isPressed(BUTTON::B)) buttonB_->execute();
}
```

## Directions for Actors

- This is powerful, but only lets us move the actor itself. Let's
  loosen that restriction and pass in the actor we want to move.

```cpp
class Command {
    public:
        virtual ~Command() {}
        void execute(GameActor& actor) = 0;
};
```

Next, we edit the comamnds slightly to act on an actor.

```cpp
class JumpCommand : public Command {
public:
    void execute(GameActor& actor) override {
        actor.jump();
    }
};
```

```cpp
Command* InputHandler::handleInput() {
    if (isPressed(Button::X)) return buttonX_;
    if (isPressed(Button::Y)) return buttonY_;
    if (isPressed(Button::A)) return buttonA_;
    if (isPressed(Button::B)) return buttonB_;

    return nullptr;
}
```

Then, in the main loop:

```cpp
Command* command = inputHandler.handleInput();
if (command) {
    command->execute(actor);
}
```

We've now made it so the Commands are decoupled from the Actor. As long
as it can receive the commands, it can execute them.

## Undo and Redo

Let's try this with a move unit command.

```cpp
class MoveUnitCommand : public Command {
public:
    MoveUnitCommand(Unit* unit, int x, int y) : unit_(unit), x_(x), y_(y) {}
    void execute() { unit_->moveTo(x_, y_); }
private:
    Unit* unit_;
    int x_;
    int y_;
};
```

This command allows us to move a unit that's passed into it.

Now we can handle its commands like so:

```cpp
Command* handleInput() {
    Unit* unit = getSelectedUnit();

    if (isPressed(Button::UP))
        return new MoveUnitCommand(unit, unit->x(), unit->y() - 1);
    if (isPressed(Button::DOWN))
        return new MoveUnitCommand(unit, unit->x(), unit->y() + 1);
    if (isPressed(Button::LEFT))
        return new MoveUnitCommand(unit, unit->x() - 1, unit->y());
    if (isPressed(Button::RIGHT))
        return new MoveUnitCommand(unit, unit->x() + 1, unit->y());

    return nullptr;
}
```

Let's make commands undoable:

```cpp
class Command {
public:
    virtual ~Command() {}
    void execute() = 0;
    void undo() = 0;
};
```

Let's add that undo method to the `MoveUnitCommand`.

```cpp
class MoveUnitCommand : public Command {
public:
    MoveUnitCommand(Unit* unit, int x, int y) : unit_(unit), xBefore_(0), yBefore_(0), x_(x), y_(y) {}
    void execute() override {
        xBefore_ = unit_->x();
        yBefore_ = unit_->y();

        unit_->moveTo(x_, y_);
    }
    void undo() override { unit_->moveTo(xBefore_, yBefore_); }
private:
    Unit* unit_;
    int xBefore_;
    int yBefore_;
    int x_;
    int y_;
};
```

Now, each unit remembers the last command it executed. If you want to
introduce undo and redo for more commands, keep a list of commands and a
reference to the current one. When a player executes a commad, we append
to the list and point current to it.

Next: [flyweight](flyweight.md)
