---
title: learn-you-a-haskell-chapter-3
---

You A Haskell Chapter 3

# Types and Typeclasses

## Believe the type

use :t to find the type of an expression :: means has type of

```hs
:t 'a'
-- 'a' :: Char
```

we can give explicit type declarations for functions as well:

```hs
removeNonUppercase :: String -> String
removeNonUppercase st = [c | c <- st, c `elem` ['A'..'Z']]

addThree :: Int -> Int -> Int -> Int
addThree x y z = x + y + z
```

the types are separated by -\>, and the last is the return type

Int stands for Integer. This is a 64-bit number on a 64 bit machine. the
min and max bounds can be found like so:

```hs
minBound :: Int
-- -9223372036854775808
maxBound :: Int
-- 9223372036854775807
```

Integer is unbounded so you can use it for really large numbers

```hs
factorial :: Integer -> Integer
factorial n = product [1..n]
factorial 50
-- 30414093201713378043612608166064768844377641568960512000000000000
```

Float is a real floating point with single precision

```hs
circumference :: Float -> Float
circumference r = 2 _ pi _ r
circumference 4.0
-- 25.132742
```

Double has double the precision

```hs
circumference' :: Double -> Double
circumference' r = 2 _ pi _ r
circumference' 4.0
-- 25.132741228718345
```

Bool is a boolean type, which can be True or False. Booleans can be
negated with `not`, and `pred` and `succ` can be used on them as well

```hs
True
-- True
False
-- False
succ False
-- True
pred True
-- False
not True
-- False
not False
-- True
```

Chars are characters, \[Char\] is a list of Chars, or a String

## Type Variables

Head takes a list of any type and returns an element of that type, a.

```hs
:t head
-- head :: [a] -> a
```

First takes a tuple with generic types (a, b) and returns a type of
\'a\'.

```hs
:t fst
-- fst :: (a, b) -> a
```

## Typeclasses 101

the type of the (==) function is:

```hs
:t (==)
-- (==) :: (Eq a) => a -> a -> Bool
```

This means that the function has a constraint of Eq a that must be met.
If the types are not equalable, this has no effect. all of the
comparison operators, like /=, ==, require Eq.

Ord is for types that have an ordering. this type is required for \>,
\<, \>=, \<=

```hs
:t (>)
-- (>) :: (Ord a) => a -> a -> Bool
```

To satisfy `Ord`, you must have the `Eq` typeclass as well.

Ord must return an Ordering, which is a type where if all members are
compared, they return GT, LT, or EQ.

Members of the typeclass `Show` can be presented as strings. You can
overload `show` for this\`.

```hs
show 3
-- "3"
show 5.334
-- "5.334"
show True
-- "True"
```

Read is the opposite typeclass of Show. Read takes a string and
transforms it to its prior representation.

```hs
read "True" || False
-- True
read "8.2" + 3.8
-- 12.0
read "5" - 2
-- 3
read "[1,2,3,4]" ++ [3]
-- [1,2,3,4,3]
```

Read \"4\" doesn\'t work, since ghci doesn\'t know what we\'re doing

```hs
read "4"
<interactive>:1:0:
Ambiguous type variable `a' in the constraint: `Read a' arising from a use of `read' at <interactive>:1:0-7
Probable fix: add a type signature that fixes these type variable(s)
```

As it says, we can use an explicit type annotation

```hs
read "5" :: Int
-- 5
read "5" :: Float
-- 5.0
(read "5" :: Float) \* 4
-- 20.0
read "[1,2,3,4]" :: [Int]
-- [1,2,3,4]
read "(3, 'a')" :: (Int, Char)
-- (3, 'a')
```

Enum members are sequentially ordered types. We can use succ and pred on
them Enum Types: (), Bool, Char, Ordering, Int, Integer, Float and
Double.

```hs
['a'..'e']
-- "abcde"
[LT .. GT]
-- [LT,EQ,GT]
[3 .. 5]
-- [3,4,5]
succ 'B'
-- 'C'
```

Bounded members have an upper and lower bound

```hs
minBound :: Int
-- -2147483648
maxBound :: Char
-- '\1114111'
maxBound :: Bool
-- True
minBound :: Bool
-- False
```

Tuples can be bounded if the components are

```hs
maxBound :: (Bool, Int, Char)
-- (True,2147483647,'\1114111')
```

Num is a numeric typeclass that can act like a number. Multiplication
can accept any number like thing.

```hs
:t (_)
-- (_) :: (Num a) => a -> a -> a
```

Integral includes only whole numbers, Int and Integer.

Floating includes only floating point numbers, Float and Double.

Prev:
\[learn-you-a-haskell-chapter-2](learn-you-a-haskell-chapter-2.md)
Next:
\[learn-you-a-haskell-chapter-4](learn-you-a-haskell-chapter-4.md)
