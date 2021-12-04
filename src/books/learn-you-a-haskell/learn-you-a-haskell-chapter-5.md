---
title: learn-you-a-haskell-chapter-5
---

You A Haskell Chapter 5

# Recursion

Recursion allows us to do computation by using the previous function\'s
state.

## Maximum awesome

How would you implement the maximum function with this signature?

```hs
maximum' :: (Ord a) => [a] -> a
```

First, you would have to handle the empty case:

```hs
maximum' [] = error "No maximum of empty list"
```

Next, you would have to handle the case where there\'s one element:

```hs
maximum' [x] = x
```

Finally, you handle the case by binding a variable to return

```hs
maximum' (x:xs)
    | x > maxTail = x
    | otherwise = maxTail
    where maxTail = maximum' xs
```

Combining all of these together, we get:

```hs
maximum' :: (Ord a) => [a] -> a
maximum' [] = error "maximum of empty list"
maximum' [x] = x
maximum' (x:xs)
    | x > maxTail = x
    | otherwise = maxTail
    where maxTail = maximum' xs
```

We can also use the standard library\'s max function:

```hs
maximum' :: (Ord a) => [a] -> a
maximum' [] = error "maximum of empty list"
maximum' [x] = x
maximum' (x:xs) = max x (maximum' xs)
```

## A few more recursive functions

Create the function `replicate`. `replicate 3 5` returns `[5, 5, 5]`.

```hs
replicate' :: (Num i, Ord i) => i -> a -> [a]
replicate' n x
    | n <= 0    = []
    | otherwise = x:replicate' (n-1) x
```

We return an empty list if n \< 0, otherwise, call replicate with n - 1
and the same x prepended to it.

As another note, since Num does not conform to Ord, we have to ask for
both of them.

Let\'s implement `take`.

```hs
take' :: (Num i, Ord i) => i -> [a] -> [a]
take' n _
    | n <= 0   = []
take' _ []     = []
take' n (x:xs) = x : take' (n-1) xs
```

If n is less than or equal to 0, return `[]`. If the list to take from
is an empty list, return an empty list. otherwise, take the first
element from the list, prepend it to the result of (take\' (n-1) xs.

Let\'s implement `reverse`.

```hs
reverse' :: [a] -> [a]
reverse' [] = []
reverse' (x:xs) = reverse' xs ++ [x]
```

If there\'s an empty list, return the empty list. Otherwise, append the
head of the list to the reverse of the rest of the list.

We can also implement repeat: just return the element and pass it to the
function again.

```hs
repeat' :: a -> [a]
repeat' x = x:repeat' x
```

How about zip?

The edge cases are if either list is empty, then return an empty list.
Otherwise, zip returns the first two elements in a tuple concatenated
with the rest of the elements.

```hs
zip' :: [a] -> [b] -> [(a, b)]
zip' _ [] = []
zip' [] _ = []
zip' (x:xs, (y:ys) = (x,y):zip' xs ys
```

How about `elem`, which takes an element and a list and checks if that
element is in the list?

```hs
elem' :: (Eq a) => a -> [a] -> Bool
elem' a [] = False
elem' a (x:xs)
  | a == x = True
  | _ = a `elem'` xs
```

Quicksort is the posterchild of haskell: you can implement it really
easily with haskell

```hs
quicksort :: (Ord a) => [a] -> [a]
quicksort [] = []
quicksort (x:xs) =
  let smallerSorted = quicksort [a | a <- xs, a <= x]
  largerSorted = quicksort [a | a <- xs, a > x]
  in smallertSorted ++ [x] ++ largerSorted
```

Prev:
\[learn-you-a-haskell-chapter-4](learn-you-a-haskell-chapter-4.md)
Next:
\[learn-you-a-haskell-chapter-6](learn-you-a-haskell-chapter-6.md)
