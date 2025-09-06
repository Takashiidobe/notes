---
title: Methods Common to All Objects
date created: Tuesday, August 5th 2025, 10:44:59 am
date modified: Tuesday, August 5th 2025, 8:18:27 pm
---

# Methods Common to All Objects

Prev: [creating-and-destroying-objects](creating-and-destroying-objects.md)
Next: [classes-and-interfaces](classes-and-interfaces.md)

# 10. Obey the General Contract when Overriding Equals

Don't override equals if:
1. Each instance of the class is inherently unique
2. There is no need for the class to have equality
3. A superclass has overridden equals, and it is suitable
4. The class is private or package-private, and its equals will not be invoked

Equals must follow these properties:

1. Reflexivity: for any non-null reference, `x.equals(x)` returns true.
2. Symmetric: `x.equals(y)` should equal `y.equals(x)` if they are both non-null
3. Transitive: if `x.equals(y)` and `y.equals(z)` returns true, `x.equals(z)` should be true for non-null references
4. Consistent: `x.equals(y)` must always return the same result as long as x or y have not changed which is used in the `equals` method.
5. Non-nullability: For any non-null reference, `x`, `x.equals(null)` must be false

Also, always override hashCode when you override equals.

Note that record classes auto generate equals, hashCode, and toSTring.

# 11. Always Override hashCode when You Override Equals

`hashcode` allows an object to be placed in HashSet or HashMap, TreeSet, TreeMap.

It can look something like this (or use lombok to autogenerate it)

```java
@Override public int hashCode() {
	int result = Short.hashCode(areaCode);
	result = 31 * result + Short.hashCode(prefix);
	result = 31 * result + Short.hashCode(lineNum);
	return result;
}
```

# 12. Always Override `toString`

`toString` makes your class more pleasant to use and debug. You should also include all the interesting information in the object:

```java
/**
* Returns the string representation of this phone number.
* The string consists of twelve characters whose format is
* "XXX-YYY-ZZZZ", where XXX is the area code, YYY is the
* prefix, and ZZZZ is the line number. Each of the capital
* letters represents a single decimal digit.
*
* If any of the three parts of this phone number is too small
* to fill up its field, the field is padded with leading zeros.
* For example, if the value of the line number is 123, the last
* four characters of the string representation will be "0123".
*/
@Override public String toString() {
	return String.format("%03d-%03d-%04d", areaCode, prefix, lineNum);
}
```

# 13. Override `clone` Judiciously

Clone is a mixin that advertises that an object can be cloned, which is a cheap field by field copy of the object. 

However, clone itself doesn't require any methods to be implemented.

```java
// Clone method for class with no references to mutable state
@Override public PhoneNumber clone() {
	try {
		return (PhoneNumber) super.clone();
	} catch (CloneNotSupportedException e) {
		throw new AssertionError(); // Can't happen
	}
}
```

# 14. Consider Implementing Comparable

`compareTo` is the method that implements sorting, and it allows for a natural ordering. To do this, implement the `Comparable` interface:

```java
public interface Comparable<T> {
	int compareTo(T t);
}
```

Also, avoid using `<` and `>` operators -- use `compare` itself when comparing fields for implementing `Comparable`

Prev: [creating-and-destroying-objects](creating-and-destroying-objects.md)
Next: [classes-and-interfaces](classes-and-interfaces.md)
