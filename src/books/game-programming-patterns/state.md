---
title: state
---

# State

The state pattern allows an object to alter its behavior when its
internal state changes.

## We've all been there

Let's make a game where the heroine jumps to some input.

```cpp
void Heroine::handleInput(Input input) {
  if (input == PRESS_B) {
    yVelocity_ = JUMP_VELOCITY;
    setGraphics(IMAGE_JUMP);
  }
}
```

Spot the bug?

You can keep jumping infinitely while you're in the air.

Add an `isJumping_` boolean to address that.

```cpp
void Heroine::handleInput(Input input) {
  if (input == PRESS_B) {
    if (!isJumping_) {
      isJumping_ = true;
      yVelocity_ = JUMP_VELOCITY;
      setGraphics(IMAGE_JUMP);
    }
  }
}
```

Next, we want her to be able to duck.

```cpp
void Heroine::handleInput(Input input) {
  if (input == PRESS_B) {
    // Jump if not jumping...
  }
  else if (input == PRESS_DOWN) {
    if (!isJumping_) {
      setGraphics(IMAGE_DUCK);
    }
  }
  else if (input == RELEASE_DOWN) {
    setGraphics(IMAGE_STAND);
  }
}
```

1.  The player can press down to duck.
2.  Press B to jump from ducking
3.  Release down while still in the air.

```cpp
void Heroine::handleInput(Input input) {
  if (input == PRESS_B) {
    if (!isJumping_ && !isDucking_) {
      // Jump...
    }
  }
  else if (input == PRESS_DOWN) {
    if (!isJumping_) {
      isDucking_ = true;
      setGraphics(IMAGE_DUCK);
    }
  }
  else if (input == RELEASE_DOWN) {
    if (isDucking_) {
      isDucking_ = false;
      setGraphics(IMAGE_STAND);
    }
  }
}
```

The code gets buggier and more error prone as we add to it.

## Finite State Machines to the Rescue

Instead, you draw a state machine, where each state can transition to
another in a fixed set of ways.

1.  There are a fixed set of states.
2.  The machine can only be in one state at a time.
3.  A sequence of events is sent to the machine.
4.  Each state has a set of transitions.

Let's model the states through enums:

```cpp
enum class State {
  STANDING,
  JUMPING,
  DUCKING,
  DIVING,
};
```

Now, we can handle input by switching on state.

```cpp
void Heroine::handleInput(Input input) {
  switch (state_) {
    case State::STANDING:
      if (input == PRESS_B) {
        state_ = State::JUMPING;
        yVelocity_ = JUMP_VELOCITY;
        setGraphics(IMAGE_JUMP);
      }
      else if (input == PRESS_DOWN) {
        state_ = State::DUCKING;
        setGraphics(IMAGE_DUCK);
      }
      break;

    case State::JUMPING:
      if (input == PRESS_DOWN) {
        state_ = State::DIVING;
        setGraphics(IMAGE_DIVE);
      }
      break;

    case State::DUCKING:
      if (input == RELEASE_DOWN) {
        state_ = State::STANDING;
        setGraphics(IMAGE_STAND);
      }
      break;
  }
}
```

What happens if we want to implement a `chargeTime_` field to Heroine?

```cpp
void Heroine::update() {
  if (state_ == State::Ducking) {
    chargeTime_++;
    if (chargeTime_ > MAX_CHARGE) {
      superBomb();
    }
  }
}
```

Ducking resets the timer, so we have to change that on the ducking
state.

```cpp
void Heroine::handleInput(Input input) {
  switch (state_) {
    case State::STANDING:
      if (input == PRESS_DOWN) {
        state_ = State::DUCKING;
        chargeTime_ = 0;
        setGraphics(IMAGE_DUCK);
      }
      // Handle other inputs...
      break;

      // Other states...
  }
}
```

## The State Pattern

Allow an object to alter its behavior when its internal state changes.
The object will appear to change its class.

### A state interface

We define an interface for the state. Let's make an abstract base
class:

```cpp
class HeroineState {
  public:
    virtual ~HeroineState() {}
    virtual void handleInput(Heroine& heroine, Input input) {}
    virtual void update(Heroine& heroine) {}
};
```

### Classes for each state

For each state, define a class that implements the interface.

```cpp
class DuckingState : public HeroineState {
public:
  DuckingState() : chargeTime_(0) {}

  virtual void handleInput(Heroine& heroine, Input input) {
    if (input == RELEASE_DOWN) {
      // Change to standing state...
      heroine.setGraphics(IMAGE_STAND);
    }
  }

  virtual void update(Heroine& heroine) {
    chargeTime_++;
    if (chargeTime_ > MAX_CHARGE) {
      heroine.superBomb();
    }
  }

private:
  int chargeTime_;
};
```

Now, we give the heroine a pointer to her current state, and delegate to
the state.

```cpp
class Heroine {
public:
  virtual void handleInput(Input input) {
    state_->handleInput(*this, input);
  }

  virtual void update() {
    state_->update(*this);
  }

  // Other methods...
private:
  HeroineState* state_;
};
```

## Where are the State Objects?

How do we store each state?

### Static states

We can make it static on the base state class:

```cpp
class HeroineState {
public:
  static StandingState standing;
  static DuckingState ducking;
  static JumpingState jumping;
  static DivingState diving;

  // Other code...
};
```

To make the heroine jump, the standing state would look like this:

```cpp
if (input == PRESS_B) {
  heroine.state_ = &HeroineState::jumping;
  heroine.setGraphics(IMAGE_JUMP);
}
```

### Instantiated states

We might make it so the update method can set the state after the
action.

```cpp
void Heroine::handleInput(Input input) {
  HeroineState* state = state_->handleInput(*this, input);
  if (state != NULL) {
    delete state_;
    state_ = state;
  }
}
```

## Enter and Exit Actions

We really want a hook to allow the state machine to do something when
entering and exiting a state.

When the heroine changes state, we also switch her sprite.

Let's handle that by giving the state an entry action:

```cpp
class StandingState : public HeroineState {
public:
  virtual void enter(Heroine& heroine) {
    heroine.setGraphics(IMAGE_STAND);
  }

  // Other code...
};
```

Then, on the handleInput, we let it call the enter action on the new
state.

```cpp
void Heroine::handleInput(Input input) {
  HeroineState* state = state_->handleInput(*this, input);
  if (state != NULL) {
    delete state_;
    state_ = state;

    // Call the enter action on the new state.
    state_->enter(*this);
  }
}
```

The ducking code looks like this now:

```cpp
HeroineState* DuckingState::handleInput(Heroine& heroine,
                                        Input input) {
  if (input == RELEASE_DOWN) {
    return new StandingState();
  }

  // Other code...
}
```

## What's the Catch?

We cant use FSMs for anything more complicated than a set of states.
Game AI, for example, is very difficult to code this way.

### Concurrent State Machines

What happens if we want to add a gun to our heroine? Well, instead of
packing all the state into one machine, where there are (n * m) states,
we can make two different state machines, for (n + m) states.

We give her another state machine for the equipment she's using.

```cpp
class Heroine {
  private:
    HeroineState* state;
    HeroineState* equipment_;
};
```

When the heroine delegates inputs to the states, she hands it to both of
them:

```cpp
void Heroine::handleInput(Input input) {
  state_->handleInput(*this, input);
  equipment_->handleInput(*this, input);
}
```

If the two states interact with each other, you'll need to sprinkle in
some `ifs` here and there, but it works.

## Hierarchical State Machines

What happens if we have a state that duplicates most of a parent state?
We can use inheritance to handle these inputs.

```cpp
class OnGroundState : public HeroineState {
public:
  virtual void handleInput(Heroine& heroine, Input input) {
    if (input == PRESS_B) {
      // Jump...
    }
    else if (input == PRESS_DOWN) {
      // Duck...
    }
  }
};
```

Each substate inherits it:

```cpp
class DuckingState : public OnGroundState {
public:
  virtual void handleInput(Heroine& heroine, Input input) {
    if (input == RELEASE_DOWN) {
      // Stand up...
    }
    else {
      // Didn't handle input, so walk up hierarchy.
      OnGroundState::handleInput(heroine, input);
    }
  }
};
```

If each child state can't handle the state, it delegates up the chain.

## Pushdown Automata

What happens if we want to transition to a new state with this approach?
Well, using a vanilla state machine, we forget what state we were in
after we transition. In order to get around that limitation, we can keep
a stack of states. The top of the stack is the last state you were in.

## So How Useful Are They?

Finite state machines are useful when:

1.  You have an entity whose behavior changes based on some internal
    state.
2.  That state can be rigidly divided into one of a relatively small
    number of distinct options.
3.  The entity responds to a series of inputs or events over time.

Prev: [singleton](singleton.md) Next:
[double-buffer](double-buffer.md)
