---
title: How Logic Gates Make Computers
date created: Saturday, August 3rd 2024, 7:29:52 pm
date modified: Saturday, November 9th 2024, 7:20:57 am
---
# How Logic Gates Make Computers

Sources:  <https://www.youtube.com/watch?v=QZwneRb-zqA>
<https://www.youtube.com/watch?v=I0-izyq6q5s>


An AND gate can be made of two switches, where a light turns on if both
A and B are closed, and the light is off otherwise.

A NOT gate can be made with one switch, where if the switch is closed,
the light is off, and if the switch is open, the light is on.

We can combine both of these gates, by wiring two switches to an AND
gate and then wiring the AND gate to a NOT gate to create a NAND gate.

You can take two NOT gates and put them with a NAND gate to create an OR
gate.

You can wire up two signals to both a NAND and OR gate and then put them
as inputs to an AND gate. This creates the XOR gate.

You can use the XOR, NAND, and OR gates to make an adder, and chain
adders together to make an n-bit adder.

You can then turn adders into an ALU that supports subtraction by using
an XOR gate with adders to make an adder and subtractor.

A set-reset latch, or a flip-flop can be created using an OR, NOT and
AND gate.

You can use two ANDs, a NOT, and NOR gates to create a data latch, which
stores memory.

Latches can be put together to make registers, which are asynchronous.
Finally, a clock tick can be used to make all signals run synchronously.
