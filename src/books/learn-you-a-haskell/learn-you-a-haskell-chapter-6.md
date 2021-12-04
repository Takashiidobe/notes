---
title: learn-you-a-haskell-chapter-6
---

You A Haskell Chapter 6

# Higher Order Functions

Haskell functions can take functions as parameters and return functions
as values. A function that does so is called a higher order function.

## Curried Functions

Functions in haskell only take one parameter -- any functions that take
more are actually curried functions.

For example, taking the max of two numbers:

```hs
max 4 5
```

is just like this:

```hs
(max 4) 5
```

remember the type of max is this:

```hs
max :: Ord a => a -> a -> a
```

For this example:

```hs
multThree :: (Num a) => a -> a -> a -> a
multThree x y z = x * y * z
```

we can compose this function with some other ones like so:

```hs
ghci> let multTwoWithNine = multThree 9
ghci> multTwoWithNine 2 3
54
ghci> let multWithEighteen = multTwoWithNine 2
ghci> multWithEighteen 10
180
```

We can compare any number with 100 like so:

```hs
compareWithHundred :: (Num a, Ord a) => a -> Ordering
compareWithHundred x = compare 100 x
```

Infix functions can be partially applied using sections.

```hs
divideByTen :: (Floating a) => a -> a
divideByTen = (/10)
```

What about a function that checks if a character supplied to it is
uppercase?

```hs
isUpperAlphanum :: Char -> Bool
isUpperAlpanum = (`elem` ['A'..'Z'])
```

Let's create a function that applies a function twice

```hs
applyTwice :: (a -> a) -> a -> a
applyTwice f x = f (f x)
```

and let's use it

```hs
ghci> applyTwice (+3) 10
16
ghci> applyTwice (++  "HEY"
"HEY HAHA HAHA"
ghci> applyTwice ("HAHA " ++) "HEY"
"HAHA HAHA HEY"
ghci> applyTwice (multThree 2 2) 9
144
ghci> applyTwice (3:) [1]
[3,3,1]
```

Let's make zipWith, which takes a function and two lists. it applies
the function to both of the lists and returns a new list.

```hs
zipWith' :: (a -> b -> c) -> [a] -> [b] -> [c]
zipWith' _ [] _ = []
zipWith' _ _ [] = []
zipWith' f (x:xs) (y:ys) = f x y : zipWith' f xs ys
```

```hs
ghci> zipWith' (+) [4,2,5,6] [2,6,2,3]
[6,8,7,9]
ghci> zipWith' max [6,3,2,1] [7,3,1,5]
[7,3,2,5]
ghci> zipWith' (++) ["foo ", "bar ", "baz "] ["fighters", "hoppers", "aldrin"]
["foo fighters","bar hoppers","baz aldrin"]
ghci> zipWith' (*) (replicate 5 2) [1..]
[2,4,6,8,10]
ghci> zipWith' (zipWith' (*)) [1,2,3],[3,5,6],[2,3,4]] [3,2,2],[3,4,5],[5,4,3]]
[3,4,6],[9,20,30],[10,12,12]]
```

we can also implement `flip`, which takes a function and returns a
function that is like the function provided, just with the two arguments
flipped.

```hs
flip' :: (a -> b -> c) -> (b -> a -> c)
flip' f = g
    where g x y = f y x
```

We can simplify this by noticing that functions are curried:

```hs
flip' :: (a -> b -> c) -> b -> a -> c
flip' f y x = f x y
```

```hs
ghci> flip' zip [1,2,3,4,5] "hello"
[('h',1),('e',2),('l',3),('l',4),('o',5)]
ghci> zipWith (flip' div) [2,2..] [10,8,6,4,2]
[5,4,3,2,1]
```

### Maps and Filters

`map` takes a function and a list and applies that function to every
element in the list.

```hs
map :: (a -> b) -> [a] -> [b]
map _ [] = []
map f (x:xs) = f x : map f xs
```

```hs
ghci> map (+3) [1,5,3,1,6]
[4,8,6,4,9]
ghci> map (++  ["BIFF", "BANG", "POW"]
["BIFF!","BANG!","POW!"]
ghci> map (replicate 3) [3..6]
[3,3,3],[4,4,4],[5,5,5],[6,6,6]]
ghci> map (map (^2)) [1,2],[3,4,5,6],[7,8]]
[1,4],[9,16,25,36],[49,64]]
ghci> map fst [(1,2),(3,5),(6,3),(2,6),(2,5)]
[1,3,6,2,2]
```

`filter` takes a predicate function and if the function evaluates to
true, keeps that element.

```hs
filter :: (a -> Bool) -> [a] -> [a]
filter _ [] = []
filter p (x:xs)
    | p x = x : filter p xs
    | _ = filter p xs
```

```hs
ghci> filter (>3) [1,5,3,2,1,6,4,3,2,1]
[5,6,4]
ghci> filter (==3) [1,2,3,4,5]
[3]
ghci> filter even [1..10]
[2,4,6,8,10]
ghci> let notNull x = not (null x) in filter notNull [1,2,3],[],[3,4,5],[2,2],[],[],[]]
[1,2,3],[3,4,5],[2,2]]
ghci> filter (`elem` ['a'..'z']) "u LaUgH aT mE BeCaUsE I aM diFfeRent"
"uagameasadifeent"
ghci> filter (`elem` ['A'..'Z']) "i lauGh At You BecAuse u r aLL the Same"
"GAYBALLS"
```

Here's the previous chapter's quicksort with Filters

```hs
quicksort :: (Ord a) => [a] -> a
quicksort [] = []
quicksort (x:xs) =
    let smaller = quicksort (filter (<= x) xs)
        larger = quicksort (filter (>x) xs)
    in smaller ++ [x] ++ larger
```

Finding the largest number under 100,000 that's divisible by 3829.

```hs
largestDivisible :: (Integral a) => a
largestDivisible = head (filter p [100000,99999..])
    where p x = x `mod` 3829 == 0
```

find the sum of all odd squares that are smaller than 10,000.

```hs
ghci> sum (takeWhile (<10000) (filter odd (map (^2) [1..])))
166650
```

### Lambdas

Lambdas are expressions that can take any number of arguments and be
passed to any function. When applied, they return a value.

This map sums up the pairs here and returns a list:

```hs
map ((a,b) -> a + b) [(1,2),(3,5),(6,3),(2,6),(2,5)]
```

### Folds

Let's implement sum using a fold:

```hs
sum' :: (Num a) => [a] -> a
sum' xs = foldl (acc x -> acc + x) 0 xs
```

```hs
ghci> sum' [3,5,2,1]
11
```

If we apply the addition function to all arguments however, we can do
this more succinctly:

```hs
sum' :: (Num a) => [a] -> a
sum' = foldl (+) 0
```

`foldr` works the same way, except it approaches from the right hand
side:

```hs
map' :: (a -> b) -> [a] -> [b]
map' f xs = foldr (x acc -> f x : acc) [] xs
```

One caveat why `foldr` exists is that it works on infinite lists, but
`foldl` will never terminate.

`foldl1` uses the first element as the accumulator: `foldr1` uses the
last element as the accumulator:

```hs
sum' :: (Num a) => [a] -> a
sum' = foldl1 (+)
```

Here are some library functions using folds

```hs
maximum' :: (Ord a) => [a] -> a
maximum' = foldr1 (x acc -> if x > acc then x else acc)

reverse' :: [a] -> [a]
reverse' = foldl (acc x -> x : acc) []

product' :: (Num a) => [a] -> a
product' = foldr1 (*)

filter' :: (a -> Bool) -> [a] -> [a]
filter' p = foldr (x acc -> if p x then x : acc else acc) []

head' :: [a] -> a
head' = foldr1 (x _ -> x)

last' :: [a] -> a
last' = foldl1 (_ x -> x)
```

`scanl` and `scanr` are similar to `foldl` and `foldr`, but they report
their intermediate states:

```hs
ghci> scanl (+) 0 [3,5,2,1]
[0,3,8,10,11]
ghci> scanr (+) 0 [3,5,2,1]
[11,8,3,1,0]
ghci> scanl1 (acc x -> if x > acc then x else acc) [3,4,5,3,7,9,2,1]
[3,4,5,5,7,9,9,9]
ghci> scanl (flip (:)) [] [3,2,1]
[],[3],[2,3],[1,2,3]]
```

Function application can be done with `$`, which evaluates the right
hand side of the equation before the left.

Instead of `sqrt (3 + 4 + 9)` we can write `sqrt $ 3 + 4 + 9`.

Function composition can be done with the `.` operator:

Instead of:

```hs
ghci> map (x -> negate (abs x)) [5,-3,-6,7,-3,2,-19,24]
[-5,-3,-6,-7,-3,-2,-19,-24]
```

We can do this:

```hs
ghci> map (negate . abs) [5,-3,-6,7,-3,2,-19,24]
[-5,-3,-6,-7,-3,-2,-19,-24]
```

Prev:
[learn-you-a-haskell-chapter-5](learn-you-a-haskell-chapter-5.md)
Next:
[learn-you-a-haskell-chapter-7](learn-you-a-haskell-chapter-7.md)
