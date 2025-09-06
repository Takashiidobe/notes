---
title: Classes and Interfaces
date created: Tuesday, August 5th 2025, 10:44:59 am
date modified: Tuesday, August 5th 2025, 9:16:54 pm
---

# Classes and Interfaces

Prev: [methods-common-to-all-objects](methods-common-to-all-objects.md)
Next: [generics](generics.md)

# 15. Minimize the Accessibility of Classes and Members

make each class or member as inaccessible as possible.

any top-level class or interface that is `public` is public, otherwise it is package-private. There are four access levels:

1. `private` only accessible from the top-level class
2. `package-private` accessible by an class in the package
3. `protected` only accessible by classes in package or subclasses
4. `public` accessible from anywhere

`public` classes are bound by API requirements, so be careful.

You can now use modules:

```java
module com.example.events {
	exports com.example.events.api;
	// all other classes are invisible to others
}
```

# 16. In Public Classes, Use Accessor Methods, not Public Fields

The author says:

```java
// Degenerate classes like this should not be public!
class Point {
	public double x;
	public double y;
}
```

Instead, `public` classes should have getters and setters, to allow you to change the data members of the class later:

```java
// Encapsulation of data by accessor methods and mutators
class Point {
	private double x;
	private double y;
	public Point(double x, double y) {
		this.x = x;
		this.y = y;
	}
	public double getX() { return x; }
	public double getY() { return y; }
	public void setX(double x) { this.x = x; }
	public void setY(double y) { this.y = y; }
}
```

I don't think this buys anything. I think this could be better as a record. At the least they say that there shouldn't be mutable fields exposed (sure) and immutable fields are questionable, but I think you could just use a record for this one (to make an immutable point), and have accessors otherwise.

Immutable classes can become records:

```java
record Point(double x, double y) {}
```

This autogenerates a constructor, getters, equals, hashCode, toString, etc:

You can also change the constructor:

```java
public record Point(Double x, Double y) {
    public Point {
        Objects.requireNonNull(x);
        Objects.requireNonNull(y);
    }
}
```

Static variables and methods can also be included:

```java
public record Person(String name, String address) {
    public static String UNKNOWN_ADDRESS = "Unknown";
}
```

```java
public record Person(String name, String address) {
    public static Person unnamed(String address) {
        return new Person("Unnamed", address);
    }
}
```

# 17. Minimize Mutability

Extremely agree with this:

1. Don't provide methods that modify the object's state
2. Ensure the class can't be extended (use final)
3. Make all fields final
4. Make all fields private
5. Ensure exclusive access to mutable components

Use records and sealed classes, and final classes as much as possible

# 18. Favor Composition over Inheritance

The author points out implementation inheritance (when one class extends another) is bad, and interface inheritance (when one class implements an interface, or an interface extends an interface) is not bad.

Implementation inheritance causes fragility. You can instead compose classes, where your new class can get a private field that references an instance of an existing class.

# 19. Design and Document for Inheritance or Else Prohibit it

Have a class document the effects of overriding any method is allows. For public or protected methods that are nonfinal (overridable) you should explain what the implementation must do to override the method.

The example provided, `java.util.AbstractCollection`'s `remove(Object o)` has to indicate how to implement it (in this case, also saying an iterator must be implemented)

Designing for inheritance is hard work -- make most classes final and non overridable.

# 20. Prefer Interfaces to Abstract Classes

Interfaces are preferred to abstract classes, because they dont have data members.

# 21. Design Interfaces for Posterity

Interfaces can be designed with a default implementation, which allow for backwards compatibility when adding a new method requirement to an interface, and easing users of the interface. 

# 22. Use Interfaces only to Define Types

Interfaces should only define types, not export constants.

# 23. Prefer Class Hierarchies to Tagged Classes

Instead of using tags to define a class hierarchy, you can now use sealed and permits

```java
sealed interface Event permits UserCreated, UserDeleted {}

record UserCreated(String id) implements Event {}
record UserDeleted(String id) implements Event{}
```

```java
switch(event) {
	case UserCreated uc -> {}
	case UserDeleted ud -> {}
}
```

# 24. Favor Static Member Classes over Nonstatic

Imagine nesting a non-static inner class. This can access the outer instance's this and private fields, and if the inner instance is long lived, then it can keep the Outer instance alive.

```java
public class Outer {
    class Inner { } // Holds implicit reference to Outer
}
```

If it's static:

Then none of those happen.

```java
public class Outer {
    public static class StaticNested { } // No reference to Outer
}
```

# 25. Limit Source Files to a Single Top-level Class

Source files should be limited to a single Top-level class per file -- `module-info.java` files in each directory can be used to export the package to other packages

```java
// module-info.java
module com.example.eventing.api {
    exports com.example.eventing.api;
}
```

Or to require an import:

```java
// module-info.java
module com.zillow.eventing.core {
    requires com.zillow.eventing.api;
}
```


Prev: [methods-common-to-all-objects](methods-common-to-all-objects.md)
Next: [generics](generics.md)
