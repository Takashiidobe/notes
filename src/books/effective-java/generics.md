---
title: Generics
date created: Tuesday, August 5th 2025, 10:44:59 am
date modified: Friday, August 8th 2025, 1:27:36 pm
---

# Generics

Prev: [classes-and-interfaces](classes-and-interfaces.md)
Next: [enums-and-annotations](enums-and-annotations.md)

# 26. Don't Use Raw Types

```java
// Don't, this loses type safety
private final Collection stamps = ...;
```

```java
// parameterized, good
private final Collection<Stamp> stamps = ...;
```

You can also use unbounded wildcard types, which can hold any item. However, this still allows you to put in a null (since all Ts are nullable)

```java
static int numElementsInCommon(Set<?> s1, Set<?> s2) {}
```

For class literals or `instanceof`, you have to use the raw type.

# 27. Eliminate Unchecked Warnings

This (I think this should be fine tbh)

```java
Set<Lark> exaltation = new HashSet();
```

Has a warning

```
warning: [unchecked] unchecked conversion
Set<Lark> exaltation = new HashSet();
                       ^
required: Set<Lark>
found: HashSet
```

You need to use the diamond operator:

```java
Set<Lark> exaltation = new HashSet<>();
```

Try to avoid warnings, and if there are any warnings still existing, suppress it with a `@SuppressWarnings("unchecked")` annotation, and a comment why it is permissible:

```java
@SuppressWarnings("unchecked")
// casting from HashSet to Set is ok
Set<Lark> exaltation = new HashSet();
```

# 28. Prefer Lists to Arrays

Arrays are covariant, which means any subtype can fit in at compile time:

```java
Object[] objectArray = new Long[1];
objectArray[0] = "what" // Throws ArrayStoreException 
```

For a list, this won't compile:

```java
List<Object> ol = new ArrayList<Long>();
ol.add("what"); // doesn't compile
```

# 29. Favor Generic Types

I agree, use generics if possible for parameterized types. Not much to say

# 30. Favor Generic Methods

Also agree, not much to say:

Turn this:

```java
public static Set union(Set s1, Set s2) {
	Set result = new HashSet(s1);
	result.addAll(s2);
	return result;
}
```

Into:

```java
public static <E> Set<E> union(Set<E> s1, Set<E> s2) {
	Set<E> result = new HashSet<>(s1);
	result.addAll(s2);
	return result;
}
```

You can use recursive type bounds as well, which come in handy:

```java
public static <E extends Comparable<E>> E max(Collection<E> c);
```

# 31. Use Bounded Wildcards to Increase API Flexibility

Assume you have this method for a stack to push all items. This only allows you to push the type E, not subtypes of E.

```java
// pushAll method without wildcard type - deficient!
public void pushAll(Iterable<E> src) {
	for (E e : src) { push(e); }
}
```

You would like to be able to add items that are also subtypes:

```java
public void pushAll(Iterable<? extends E> src) {
	for (E e : src) { push(e); }
}
```

Same with pop:

```java
public void popAll(Iterable<E> dst) {
	while(!isEmpty()) { dst.add(pop()); }
}
```

Instead, you want to be able to pop supertypes, so you would use wildcards for that:

```java
public void popAll(Collection<? super E> dst) {
	while (!isEmpty())
		dst.add(pop());
}
```

# 32: Combine Generics and Varargs Judiciously



Prev: [classes-and-interfaces](classes-and-interfaces.md)
Next: [enums-and-annotations](enums-and-annotations.md)
