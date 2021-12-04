---
title: bytecode
---

# Bytecode

## Intent

Give behavior the flexibility of data by encoding it as instructions for
a virtual machine

## Motivation

Making games requires a lot of flexibility: we need a language like C++
that has high performance and a good type system to corral bugs. C++
also takes a long time to compile, which requires constant iteration,
but we don\'t want to recompile every time. What do we do?

### Spell fight!

Let\'s make a magic-based fighting game. A pair of wizards sling spells
at each other until there is only one left.

If a game designer wants to tweak some part of the game, if we hard code
the spells into the source code, it\'ll always take a compile to make
any changes and test them out.

Also, if we want to support modding, we need some way to allow adding
spells. If we hard code all spells into the binary, we need to release
our source code and allow them to play with the source code.

### Data \> Code

We want people to be able to extend the behavior of the game by
extending data. Let\'s use files for that and contrast that with the
Interpreter pattern from the GoF.

### The Interpreter pattern

Let\'s discuss how to implement and execute the interpreter pattern.

Create an expression class:

```cpp
class Expression {
public:
  virtual ~Expression() {}
  virtual double evaluate() = 0;
};
```

Then we define a class that implements this interface for numbers.

```cpp
class NumberExpression : public Expression {
public:
  NumberExpression(double value) : value_(value) {}

  virtual double evaluate() { return value_; }

private:
  double value_;
};
```

For Addition:

```cpp
class AdditionExpression : public Expression {
public:
  AdditionExpress(Expression* left, Expression* right) : left_(left), right_(right) {}
  virtual double evaluate {
    double left = left_->evaluate();
    double right = right_->evaluate();
    return left + right;
  }
private:
  Expression* left_;
  Expression* right_;
};
```

This is beautiful and simple, but it uses a lot of pointers:

- Loading it from disk takes a long time to wire up the pointers
- Those objects and the pointers use a lot of memory. (68 bytes!)
- Traversing the pointers into subexpressions is extremely slow on the
  cache.

This is too slow and memory intensive.

### Machine code, virtually

Consider a binary from C++.

- It\'s dense
- It\'s linear
- It\'s low-level
- It\'s fast

We can\'t do the same thing, but we can add a VM to our code to run code
on the fly.

## The Pattern

An instruction set defines the low-level operations that can be
performed. A series of instructions is encoded as a sequence of bytes. A
virtual machine executes these instructions one at a time, using a stack
for intermediate values. This allows us to define complex high-level
behavior.

## When to Use It

Bytecode is slower than native code, so it comes with a performance
penalty. Use this if you want to avoid compile times and need
flexibility at runtime.

## Keep in Mind

DSLs and the like have a tendency to grow like vines. Try your best to
keep it small, or rearchitect it when needed.

### You\'ll need a front-end

You\'ll need to find some way to generate this bytecode that this
pattern interprets.

### You\'ll miss your debugger

You\'ll need to build a debugger for your language since otherwise
there\'ll be no way to debug it, which will delay you from shipping your
code.

## Sample Code

This\'ll be fairly simple: create an instruction set for the VM.

### A magical API

Let\'s start out with an API for a wizard.

```cpp
void setHealth(int wizard, int amount);
void setWisdom(int wizard, int amount);
void setAgility(int wizard, int amount);
```

And then actually doing things:

```cpp
void playSound(int soundId);
void spawnParticles(int particleType);
```

### A magical instruction set

Let\'s make an enumeration for each instruction.

```cpp
enum class Instruction : unsigned char {
  SET_HEALTH      = 0x00,
  SET_WISDOM      = 0x01,
  SET_AGILITY     = 0x02,
  PLAY_SOUND      = 0x03,
  SPAWN_PARTICLES = 0x04
};
```

Let\'s create a way to execute these instructions:

```cpp
switch (instruction) {
  case Instruction::SET_HEALTH:
    setHealth(0, 100);
    break;

  case Instruction::SET_WISDOM:
    setWisdom(0, 100);
    break;

  case Instruction::SET_AGILITY:
    setAgility(0, 100);
    break;

  case Instruction::PLAY_SOUND:
    playSound(SOUND_BANG);
    break;

  case Instruction::SPAWN_PARTICLES:
    spawnParticles(PARTICLE_FLAME);
    break;
}
```

And let\'s make a class that represents the VM.

```cpp
class VM {
public:
  void interpret(char bytecode[], int size) {
    for (int i = 0; i < size; i++) {
      char instruction = bytecode[i];
      switch (instruction) {
        // Cases for each instruction...
      }
    }
  }
};
```

## A stack machine

To execute a nested expression, you\'ll have to create a stack that
keeps track of the state and function pointers here.

```cpp
class VM {
public:
  VM() : stackSize_(0) {}

  // Other stuff...

private:
  static const int MAX_STACK = 128;
  int stackSize_;
  int stack_[MAX_STACK];
};
```

The VM needs some methods to push and pop off the stack:

```cpp
class VM {
private:
  void push(int value) {
    // Check for stack overflow.
    assert(stackSize_ < MAX_STACK);
    stack_[stackSize_++] = value;
  }

  int pop() {
    // Make sure the stack isn't empty.
    assert(stackSize_ > 0);
    return stack_[--stackSize_];
  }

  // Other stuff...
};
```

When an instruction needs to receive parameters, it pops them off the
stack and applies the instruction.

```cpp
switch (instruction) {
  case Instruction::SET_HEALTH: {
    int amount = pop();
    int wizard = pop();
    setHealth(wizard, amount);
    break;
  }

  case Instruction::SET_WISDOM:
  case Instruction::SET_AGILITY:
    // Same as above...

  case Instruction::PLAY_SOUND:
    playSound(pop());
    break;

  case Instruction::SPAWN_PARTICLES:
    spawnParticles(pop());
    break;
}
```

We also need an instruction that is a literal, which lets us pass
values.

```cpp
case Instruction::LITERAL {
  int value = bytecode[++i]; // read the next byte from bytecode
  push(value);
  break;
}
```

This is good enough to define basic behavior, but we can\'t compose any
behavior.

### Behavior = Composition

We need a way to create expressions that combine different values in
interesting ways.

We need a way to get health and be able to manipulate it.

```cpp
case Instruction::GET_HEALTH: {
  int wizard = pop();
  push(getHealth(wizard));
  break;
}
```

This way, we can read the value of the wizard and then return it back to
the stack.

We\'ll need addition though, to be able to use the getters and setters
correctly.

```cpp
case Instruction::ADD {
  int b = pop();
  int a = pop();
  push(a + b);
  break;
}
```

Let\'s say we wanted to do something like this:

    setHealth(0, getHealth(0) +
        (getAgility(0) + getWisdom(0)) / 2);

That would translate to these instructions:

```cpp
LITERAL 0    [0]            # Wizard index
LITERAL 0    [0, 0]         # Wizard index
GET_HEALTH   [0, 45]        # getHealth()
LITERAL 0    [0, 45, 0]     # Wizard index
GET_AGILITY  [0, 45, 7]     # getAgility()
LITERAL 0    [0, 45, 7, 0]  # Wizard index
GET_WISDOM   [0, 45, 7, 11] # getWisdom()
ADD          [0, 45, 18]    # Add agility and wisdom
LITERAL 2    [0, 45, 18, 2] # Divisor
DIVIDE       [0, 45, 9]     # Average agility and wisdom
ADD          [0, 54]        # Add average to current health
SET_HEALTH   []             # Set health to result
```

We use pushes and pops to get what we need.

### A virtual machine

This virtual machine is safe (since it\'s sandboxed, it can\'t reach
into other parts of the code and cause security vulnerabilities. We also
saw that it\'s as easy as implementing a stack and popping and pushing
off of it.

### Spellcasting tools

We saw that it was easy to interpret the code, but we haven\'t generated
the bytecode. We can use tools like lex or yacc to do this, but that\'s
for another time.

## Design Decisions

### How do instructions access the stack?

Stack based VMs can only push and pop from the top of the stack. They
can\'t read any other state. Register based VMs can dig into a specific
register (location) and read the content of the instruction from there.

- With a stack-based VM:

  - Instructions are small
  - Code generation is simpler
  - You have more instructions

- With a register-based VM:

  - Instructions are larger
  - You have fewer instructions

### What set of instructions do you have?

- External primitives
- Internal primitives
- Control Flow
- Abstraction (Functions as jumps)

### How are values represented?

- A single datatype:

  - It\'s simple
  - There are no different data types. (Numbers are strings and
    vice-versa)

- A tagged variant:

  - A value has a tag (which represents its type) and its values.

```cpp
enum class ValueType {
  INT,
  DOUBLE,
  STRING
};

struct Value {
  ValueType type;
  union {
    int intVal;
    double doubleVal;
    char* stringVal;
  };
};
```

- Values know their type

- It takes more memory

- An untagged union:

  - Just the value
  - It\'s fast
  - It\'s unsafe
  - (The compiler guarantees code isn\'t incorrect)

If we can stick with a single data type, do so. Otherwise, tagged unions
are good.

### How is the bytecode generated?

- A text based language

  - Less technical people will dislike it
  - More composable

- A graphical authoring tool

  - Less technical people will like it
  - Less composable

Prev: \[update-method](update-method.md) Next:
\[subclass-sandbox](subclass-sandbox.md)
