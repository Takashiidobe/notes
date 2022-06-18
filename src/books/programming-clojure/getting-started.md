---
title: "Getting Started"
---

# Getting Started

Next: [exploring-clojure](exploring-clojure.md)

In java, compare how to add an `isBlank` function to a `String`:

```java
public class StringUtils {
  public static boolean isBlank(final CharSequence str) {
    int strLen;
    if (str == null || (strLen = str.length()) == 0) {
      return true;
    }
    for (int i = 0; i < strLen; i++) {
      if (Character.isWhitespace(str.charAt(i)) == false) {
        return false;
      }
    }
    return true;
  }
}
```

This requires you to create a new class, a static method (in java, there
are no such thing as free functions, so you have to create a static
method, and you can't open the string namespace, so you have to create a
new one.

Meanwhile, the clojure one is simple:

```clj
(defn blank? [str]
  (every? #(Character/isWhitespace %) str))
```

Compare defining a simple Person class in Java:

```java
public class Person {
  private String firstName;
  private String lastName;
  public Person(String firstName, String lastName) {
    this.firstName = firstName;
    this.lastName = lastName;
  }
  public String getFirstName() {
    return firstName;
  }
  public void setFirstName(String firstName) {
    this.firstName = firstName;
  }
  public String getLastName() {
    return lastName;
  }
  public void setLastName(String lastName) {
    this.lastName = lastName;
  }
}
```

to Clojure:

```clj
(defrecord Person [first-name last-name])

(def foo(->Person "Aaron" "Bedra"))
-> #'user/foo
(:first-name foo)
-> Aaron
```

Clojure data is immutable (it uses persistent data structures), so
`hashCode()` and `equals()` are automatically derived for you:

## Clojure is Lisp Reloaded

Clojure is extendable with macros -- you can redefine keywords at will,
for many use cases. In fact, most keywords are just macros, like
defrecord:

You can even extend `defrecord` easily, if you'd like to apply strong
typing and disallow nils.

```clj
(defrecord name [Type :arg1 Type :arg2 Type :arg3]
  :allow-nils false)
```

Clojure has a few improvements over traditional lisps:

1. The list has been abstracted into a `seq` (Sequence), kind of like an
   iterable in other languages, which you can define for your own types.
2. Clojure relies on the JVM, which makes it easy to deploy
3. Symbol resolution and syntax quoting makes it easy to write many
   common macros.
4. Clojure provides a convenient literal syntax for common data
   structures, like regexps, maps, sets, vectors, and metadata.
5. Clojure treats commas as whitespace -- there's less noise.

```clj
[1,2,3,4] # valid vector
[ 1 2 3 4 ] # also valid
```

6. Clojure removes some parens found in other lisps:

```clisp
; Common Lisp cond
(cond ((= x 10) "equal")
  ((> x 10) "more"))
```

```clj
; Clojure cond
(cond (= x 10) "equal"
  (> x 10) "more")
```

## Clojure is a Functional Language

1. Functions are first class objects
2. Data is immutable
3. Functions are pure; they don't have side effects

For example, here's a list comprehension of all composers who have
written a composition named "Requiem":

(for [c compositions :when (= (:name c) "Requiem")] (:composer c))
-> ("W. A. Mozart" "Giuseppe Verdi")

This has a few desirable properties:

1. it is simple; no loops, variables, or mutable state
2. It is thread safe; no locking is needed.
3. It is parallelizable; you could split work amongst many places
4. It is generic; compositions could be anything.

## Clojure Simplifies Concurrent Programming

Clojure's functional programming and immutability make it easy to write
thread-safe code:

Next: [exploring-clojure](exploring-clojure.md)
