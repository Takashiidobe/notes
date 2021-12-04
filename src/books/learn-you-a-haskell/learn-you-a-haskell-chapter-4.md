---
title: learn-you-a-haskell-chapter-4
---

You A Haskell Chapter 4

# Syntax in Functions

## Pattern Matching

```hs
lucky :: (Integral a) => a -> String
lucky 7 = "LUCKY NUMBER SEVEN!"
lucky x = "Sorry, you're out of luck, pal!"
```

This function checks if the number passed in is 7. If it is, it returns
"LUCKY NUMBER SEVEN!", otherwise, it returns the String "Sorry,
you're out of luck, pal!".

We can make functions with capturing catch alls this way.

```hs
sayMe :: (Integral a) => a -> String
sayMe 1 = "One!"
sayMe 2 = "Two!"
sayMe 3 = "Three!"
sayMe 4 = "Four!"
sayMe 5 = "Five!"
sayMe x = "is not between 1 and 5" ++ show x
```

Or we can define a `factorial` function like so:

```hs
factorial :: (Integral a) => a -> a
factorial 0 = 1
factorial n = n * factorial (n - 1)
```

You want to define a function from the top to the bottom using a more
specific catch-all to the more general ones, otherwise they might not
work. Imagine pattern matching like a switch statement with a break at
the end of each case.

Pattern matching doesn't have to be comprehensive.

Let's say we define this:

```hs
charName :: Char -> String
charName 'a' = "Albert"
charName 'b' = "Broseph"
charName 'c' = "Cecil"
{- Notice there is no pattern for any char outside of 'a', 'b', 'c' -}
```

```sh
ghci> charName 'h'
"*** Exception: tut.hs:(53,0)-(55,21): Non-exhaustive patterns in function charName
```

Always add catch alls to patterns to make sure not to crash on
unexpected input.

Let's define a pattern that adds up two tuples with a pair of points.

```hs
addVectors :: (Num a) => (a, a) -> (a, a) -> (a, a)
addVectors (x1, y1) (x2, y2) = (x1 + x2, y1 + y2)
```

We can create our own first, second and third functions on 3-tuples as
well this way.

Remember that the `_` character means to disregard all other elements in
the match.

```hs
first :: (a, b, c) -> a
first (x, _, _) = x

second :: (a, b, c) -> b
second (_, y, _) = y

third :: (a, b, c) -> c
third (_, _, z) = z
```

You can pattern match in list comprehensions too.

Sum up all tuples in the list:

```hs
let xs = [(1,3), (4,3), (2,4), (5,3), (5,6), (3,1)]
[a+b | (a,b) <- xs]
-- [4,7,6,8,11,4]
```

We can implement our own head function this way as well

```hs
head' :: [a] -> a
head' [] = error "Can't call head on an empty list"
head' (x:_) = x
```

and use it on lists and strings:

```hs
head' [4,5,6]
-- 4
head' "Hello"
-- 'H'
```

You can show the first few items in a list this way:

```hs
tell :: (Show a) => [a] -> String
tell [] = "The list is empty"
tell (x:[]) = "The list has one element: " ++ show x
tell (x:y:[]) = "The list has two elements: " ++ show x ++ " and " ++ show y
tell (x:y:_) = "This list is long. The first two elements are: " ++ show x ++ " and " ++ show y
```

we can impleemnt our own length function as well.

if the length is empty, it returns 0. otherwise, it returns the length
of the rest of the list + 1.

```hs
length' :: (Num b) => [a] -> b
length' [] = 0
length' (_:xs) = 1 + length' xs
```

implementing sum:

```hs
sum' :: (Num a) => [a] -> a
sum' [] = 0
sum' (x:xs) = x + sum' xs
```

We can't use ++ in pattern matches.

## Guards, Guards!

guards let us check if the pattern matches a criteria:

if the pattern (a) matches a guard (boolean expressions) then it matches
that.

```hs
bmiTell :: (RealFloat a) => a -> String
bmiTell bmi
    | bmi <= 18.5 = "You're underweight, you emo, you!"
    | bmi <= 25.0 = "You're supposedly normal. Pffft, I bet you're ugly!"
    | bmi <= 30.0 = "You're fat! Lose some weight, fatty!"
    | _ = "You're a whale, congratulations!"
```

We can match with as many parameters as we want:

```hs
bmiTell :: (RealFloat a) => a -> a -> String
bmiTell weight height
    | weight / height ^ 2 <= 18.5 = "You're underweight, you emo, you!"
    | weight / height ^ 2 <= 25.0 = "You're supposedly normal. Pffft, I bet you're ugly!"
    | weight / height ^ 2 <= 30.0 = "You're fat! Lose some weight, fatty!"
    | otherwise                 = "You're a whale, congratulations!"
```

We can make our own max' function with guards as well.

```hs
max' :: (Ord a) => a -> a -> a
max' a b
  | a > b = a
  | _ = b
```

We can also make our own compare, which returns an `Ordering`.

```hs
myCompare :: (Ord a) => a -> a -> Ordering
a `myCompare` b
    | a > b     = GT
    | a == b    = EQ
    | otherwise = LT
```

we can create a variable in the where after a guard clause:

```hs
bmiTell :: (RealFloat a) => a -> a -> String
bmiTell weight height
    | bmi <= 18.5 = "You're underweight, you emo, you!"
    | bmi <= 25.0 = "You're supposedly normal. Pffft, I bet you're ugly!"
    | bmi <= 30.0 = "You're fat! Lose some weight, fatty!"
    | otherwise   = "You're a whale, congratulations!"
    where bmi = weight / height ^ 2
```

## Let it Be

You can use let bindings to bind a variable to a function locally.

```hs
[if 5 > 3 then "Woo" else "Boo", if 'a' > 'b' then "Foo" else "Bar"]
-- ["Woo", "Bar"]
4 * (if 10 > 5 then 10 else 0) + 2
-- 42
```

```hs
[let square x = x * x in (square 5, square 3, square 2)]
```

## Case expressions

You can use case expressions following this pattern:

    case expression of pattern -> result
                       pattern -> result
                       pattern -> result

We can use them like so:

```hs
describeList :: [a] -> String
describeList xs = "The list is " ++ case xs of [] -> "empty."
                                                [x] -> "a singleton list."
                                                xs -> "a longer list."
```

Prev:
[learn-you-a-haskell-chapter-3](learn-you-a-haskell-chapter-3.md)
Next:
[learn-you-a-haskell-chapter-5](learn-you-a-haskell-chapter-5.md)
