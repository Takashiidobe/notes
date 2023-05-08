# How does the Virtual Keyword work? How do Vtables work?

Virtual functions are used to support runtime polymorphism, allowing a method to call different versions at runtime.

This is useful for "interfaces" where you might call a method through a base class.

## Virtual Tables

Vtables are used to implement late binding. A class with at least one virtual member gets a pointer to a vtable in memory which contains addresses for implementations of functions. Any function that calls a virtual function looks up the corresponding function in the vtable, and calls that method at runtime.
