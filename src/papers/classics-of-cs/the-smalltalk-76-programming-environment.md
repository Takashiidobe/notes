---
title: The Smalltalk 76 Programming Environment
date created: Wednesday, October 4th 2023, 8:49:12 am
date modified: Saturday, December 7th 2024, 8:35:54 pm
---

# The Smalltalk 76 Programming Environment

The Smalltalk project, which started at Xerox Parc, was created with the purpose of allowing children to be able to use computing systems. It aimed to create a personal computing environment, where a single user could have access and control over their computer, like drawing pictures, file handling, and text editing.

The smalltalk language is object-oriented, much like simula before it. It primarily works by passing messages from one object to another. Classes have instances which share common characteristics, such as how they respond to messages.

Operators are thought of as messages that might take one or more arguments. For example, `+4` as is would apply unary `+` to 4, leaving it as 4.

## The Principle of Modularity

No part of a complex system should depend on the internal details of any other part. Objects should send messages to obtain results, and similar behavior should be grouped into classes. Factoring of the information structure and behavior is provided by subclassing.

All references in Smalltalk are to objects. They may be atomic, or consist of several named fields, which refer to other objects. Smalltalk does away with referencing memory addresses, such as getting the y coordinate in a point in a Cartesian plane by `loading the second word relative to the point p`. This would break on polar coordinates, for example. The response to a message is implemented by a method, which reads or writes a data field, or sends further messages to achieve the desired response.

Classes can inherit from each other, in which case they inherit all the traits of their parent class.

## The Reactive Principle

All objects in smalltalk are active, so they can respond to messages at any time. The libraries used to implement the system is a set of useful superclasses from which classes can derive. For example, windows are inheritable from the system library. The window class also responds to behavior, such as clicks within the window, and transitioning from active to inactive.

## Classes

Classes in smalltalk also respond to operator overloading, and have setters and getters. They also allow themselves to be turned into a string stream which can then be printed. As well, numbers can implement the full set of relational operators by only defining `<`, `=`, and `>`.
