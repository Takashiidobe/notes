---
title: "Lesson 2: Representing Programs"
---

# Lesson 2: Representing Programs

Prev: [lesson-1-welcome-and-overview](lesson-1-welcome-and-overview.md)
Next: [lesson-2-introduction-to-bril](lesson-2-introduction-to-bril.md)

We first learn how to represent programs. Programs have to be
represented somehow. The original textual syntax is not great for
optimization, but good for the human to read.

```js
let value = 8;
let result = 1;
for (let i = value; i > 0; i++) {
    result = result * i;
}
console.log(result);
```

An abstract syntax:

Programs can be represented by an Abstract Syntax Tree, which might show
the entire program in a tree representation. This is popular for
interpreters, but not as much for compilers, since this allows for
easier optimizations. Instead, the course looks at an IR that codifies
this form.

Instructions:

This instruction format is kind of like assembly, but independent and
not bound to any amount of registers. A backend implementer can set the
number of registers to use afterwards in a pass.

```
@main {
    v0: int = const 8;
    value: int = id v0;
    result: int = id v1;
    v3: int = id value;
    i: int = id v3;
.for.cond:
    v4: int = id i;
    ...
}
```

Control Flow Graphs:

- A directed graph
- Vertices are instructions
- Edges indicate possible flow of control
- One entry and one exit vertex

```
@main {
    v: int = const 5;
    print v;
}
```

The CFG looks like:

```
[const v] -> [print v]
```

```
@main {
    v: int = const 4;
    jmp .somewhere;
    v: int = const 2;
.somewhere:
    print v;
}
```

The CFG would look like this:

```
[v = 4] -> [jmp .somewhere] -> [.somewhere] -> [print v]
                                          [v = 2] /
```

Note that the v = 2 node is isolated, since it has no incoming edges. It
is thus guaranteed never to be executed.

Thus, we could have a compiler pass that operates on this CFG and never
executes code that has no incoming edges.

Thus, the representation of the program has a big effect on what
optimizations make sense.

```
@main {
    v: int = const 4;
    b: bool = const false;
    br b .there .here;
.here:
    v: int = const 2;
.there:
    print v;
}
```

In this case, `here` is always taken, and then the `there` is printed.

Since drawing each instruction as a CFG is unnecessary (since every
block is guaranteed to have all instructions execute), we can have each
block be a node and all edges can be other blocks that can be jumped to.

The last instructor of a basic block must be a terminator, which gives
up control to another node.

How do we transform a list of instructions into a list of basic blocks?

```python
blocks = []
block = []
for instruction in instructions:
    if instruction is not a label:
        block.append(instruction)
    if instruction is label or instruction is terminator:
        blocks.append(block)
        block = []
```

To then match all the blocks with their labels:

```python
for block in blocks:
    last_block = block[-1]
    if last is jmp:
        add edge from block to last.dest
    elif last_block is br:
        add two edges from block to last.true and last.false
    else:
        add node to block if exists.
```


Prev: [lesson-1-welcome-and-overview](lesson-1-welcome-and-overview.md)
Next: [lesson-2-introduction-to-bril](lesson-2-introduction-to-bril.md)
