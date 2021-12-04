---
title: learn-you-a-haskell-chapter-2
---

You A Haskell Chapter 2

# Starting Out

## Ready, Set, go!

To start coding in haskell, type in ghci.

```sh
ghci
```

```hs
2 + 15
-- 17
49 _ 100
-- 4900
1892 - 1472
-- 420
5 / 2
-- 2.5
```

We can use parentheses too:

```hs
(50 _ 100) - 4999
-- 1
50 _ 100 - 4999
-- 1
50 _ (100 - 4999)
-- -244950
```

Boolean Algebra:

```hs
True && False
-- False
True && True
-- True
False || True
-- True
not False
-- True
not (True && True)
-- False
```

Equality Testing:

```hs
5 == 5
-- True
1 == 0
-- False
5 /= 5
-- False
5 /= 4
-- True
"hello" == "hello"
-- True
```

We can't add two different types though:

```hs
5 + "llama"
-- No instance for (Num [Char])
-- arising from a use of `+' at <interactive>:1:0-9
-- Possible fix: add an instance declaration for (Num [Char])
-- In the expression: 5 + "llama"
-- In the definition of `it': it = 5 + "llama"
```

Succ and Pred return the next and previous item.

```hs
succ 8
-- 9
-- succ returns the next of an item.
pred 8
-- 7
-- pred returns the predicate, or previous of an item.
min 9 10
-- 9
min 3.4 3.2
-- 3.2
max 100 101
-- 101
succ 9 + max 5 4 + 1
-- 16
(succ 9) + max (5 4) + 1
-- 16
```

Check if a number is even or odd:

```hs
even 4
-- True
odd 5
-- True
```

## Baby's First Functions

```hs
doubleMe x = x + x

doubleUs x y = doubleMe x + doubleMe y

doubleSmallNumber x = if x > 10 then x else x * 2
```

```hs
conanO'Brien = "It's a me, Conan O'Brien!"

lostNumbers = [4,8,15,16,23,42]

[1,2,3,4] ++ [9,10,11,12]
-- [1,2,3,4,9,10,11,12]
```

use ++ to add two lists together. strings are just lists of chars.
Remember that ++ takes O(n) time

```hs
[1,2,3,4] ++ [9,10,11,12]
-- [1,2,3,4,9,10,11,12]
"hello" ++ " " ++ "world"
-- "hello world"
['w','o'] ++ ['o','t']
-- "woot"
```

whereas `:`, the cons operator takes O(1)

```hs
'A': " SMALL CAT"
-- "A SMALL CAT"
5:[1,2,3,4,5]
-- [5,1,2,3,4,5]
```

Access by index is done with `!!`.

```hs
"Steve Buscemi" !! 6
-- 'B'
[9.4,33.2,96.2,11.2,23.25] !! 1
-- 33.2

b = [1,2,3,4],[5,3,3,3],[1,2,2,3,4],[1,2,3]]
-- [1,2,3,4],[5,3,3,3],[1,2,2,3,4],[1,2,3]]
b ++ [1,1,1,1]]
-- [1,2,3,4],[5,3,3,3],[1,2,2,3,4],[1,2,3],[1,1,1,1]]
[6,6,6]:b
-- [6,6,6],[1,2,3,4],[5,3,3,3],[1,2,2,3,4],[1,2,3]]
b !! 2
-- [1,2,2,3,4]
```

Lists can be compared if they have elements that meet the typeclass Ord
Lists are compared from the head..tail

```hs
[3,2,1] > [2,1,0]
-- True
[3,2,1] > [2,10,100]
-- True
[3,4,2] > [3,4]
-- True
[3,4,2] > [2,4]
-- True
[3,4,2] == [3,4,2]
-- True
```

Head takes a list and returns its head, or first element

```hs
head [5,4,3,2,1]
-- 5
```

tail takes a list and returns its head, which is everything but the head

```hs
tail [5,4,3,2,1]
-- [5,4,3,2,1]
```

last takes a list and returns its last element

```hs
last [5,4,3,2,1]
-- 1
```

init takes a list and returns everything except its last element

```hs
init [5,4,3,2,1]
-- [5,4,3,2]
```

using any of the above blows up on an empty list

```hs
head []
-- *** Exception: Prelude.head: empty list
```

length takes a list and returns its length

```hs
length [5,4,3,2,1]
-- 5
```

null checks if a list is empty. If it is, it returns True, else, False

```hs
null [1,2,3]
-- False
null []
-- True
```

reverse reverses a list

```hs
reverse [5,4,3,2,1]
-- [1,2,3,4,5]
```

take takes from the beginning of the list

```hs
take 3 [5,4,3,2,1]
-- [5,4,3]
take 1 [3,9,3]
-- [3]
take 5 [1,2]
-- [1,2]
take 0 [6,6,6]
-- []
```

drop works in a similar way, but it drops elements then takes the
remaining elements.

```hs
drop 3 [8,4,2,1,5,6]
-- [1,5,6]
drop 0 [1,2,3,4]
-- [1,2,3,4]
drop 100 [1,2,3,4]
-- []
```

maximum and minimum returns the max and minimum of a list

```hs
minimum [8,4,2,1,5,6]
-- 1
maximum [1,9,2,3,4]
-- 9
```

sum takes a list of numbers and returns their sum

```hs
sum [1,2,3,4]
-- 10
```

product takes a list of numbers and returns their product

```hs
product [1,2,3,4]
-- 24
```

elem takes a thing and a list of things and tells us if that thing is an
element of the list.

```hs
4 `elem` [3,4,5,6]
-- True
10 `elem` [3,4,5,6]
-- False
```

## Texas Ranges

ranges are defined for elements that have a succ

```hs
[1..20]
-- [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20]
['a'..'z']
-- "abcdefghijklmnopqrstuvwxyz"
['K'..'Z']
-- "KLMNOPQRSTUVWXYZ"
```

steps can be specified as the first element before the comma

```hs
[2,4..20]
-- [2,4,6,8,10,12,14,16,18,20]
[3,6..20]
-- [3,6,9,12,15,18]
```

ranges in reverse have to be specified with the first element

```hs
[20,19..1]
-- [20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1]
```

be careful about floats in haskell.

```hs
[0.1, 0.3 .. 1]
-- [0.1,0.3,0.5,0.7,0.8999999999999999,1.0999999999999999]
```

ranges can be lazy, just don't end the right hand side

```hs
x = [13,26..]
-- x
take 3 x
-- [13,26,39]
```

cycle takes a list and cycles it into an infinite list

```hs
take 10 (cycle [1,2,3])
-- [1,2,3,1,2,3,1,2,3,1]
take 12 (cycle
-- "LOL LOL LOL "
```

repeat takes an element and produces an infinite list of that element

```hs
take 10 (repeat 5)
-- [5,5,5,5,5,5,5,5,5,5]
```

(replicate times item) returns the same element x times

```hs
replicate 3 10
-- [10, 10, 10]
```

List comprehensions

```hs
[x*2 | x <- [1..10]]
-- [2,4,6,8,10,12,14,16,18,20]
```

with an if block, only take items that are greater than 12.

## I'm a list comprehension

```hs
[x*2 | x <- [1..10], x*2 >= 12]
-- [12,14,16,18,20]
```

```hs
boomBangs xs = [ if x < 10 then "BOOM!" else "BANG!" | x <- xs, odd x]
boomBangs [7..13]
-- ["BOOM!","BOOM!","BANG!","BANG!"]
```

list comprehensions can be used for outer joins as well

```hs
let nouns = ["hobo","frog","pope"]
let adjectives = ["lazy","grouchy","scheming"]
[adjective ++ " " ++ noun | adjective <- adjectives, noun <- nouns]
-- ["lazy hobo","lazy frog","lazy pope","grouchy hobo","grouchy frog", "grouchy pope","scheming hobo","scheming frog","scheming pope"]
```

we can define our own length by replacing everything with 1 and summing
it up.

```hs
length' xs = sum [1 | _ <- xs]
```

remove nonuppercase characters

```hs
removeNonUppercase st = [ c | c <- st, c `elem` ['A'..'Z']]
```

## Tuples

tuples are like non-homogenous lists

```hs
tup = (1,

fst tup
-- 8
snd tup
-- "hi"
```

zip produces a list of pairs

```hs
zip [1,2,3,4,5] [5,5,5,5,5]
-- [(1,5),(2,5),(3,5),(4,5),(5,5)]

zip [1 .. 5] ["one", "two", "three", "four", "five"]
-- [(1,]

let rightTriangles = [ (a,b,c) | c <- [1..10], b <- [1..c], a <- [1..b], a^2 + b^2 == c^2]
-- [(3,4,5), (6,8,10)]
```

Prev:
[learn-you-a-haskell-chapter-1](learn-you-a-haskell-chapter-1.md)
Next:
[learn-you-a-haskell-chapter-3](learn-you-a-haskell-chapter-3.md)
