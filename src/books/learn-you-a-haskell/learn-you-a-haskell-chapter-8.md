---
title: learn-you-a-haskell-chapter-8
---

# Making our Own Typeclasses

## Algebraic Data types intro

Let's see how `Bool` is implemented.

```hs
data Bool = False | True
```

a bool is either False or True.

Here's how Int is defined:

```hs
data Int = -214783648 | ... | -1 | 0 | 1 | ... | 214783647
```

Let's make our own type to represent a shape:

```hs
data Shape = Circle Float Float Float | Rectangle Float Float Float Float
```

A Shape can either be a Circle that takes three Float values, or a
Rectangle, which takes four Float values.

```hs
ghci> :t Circle
Circle :: Float -> Float -> Float -> Shape
ghci> :t Rectangle
Rectangle :: Float -> Float -> Float -> Float -> Shape
```

Let's make a function that takes a Shape and returns its area.

```hs
surface :: Shape -> Float
surface (Circle _ _ r) = pi * r ^ 2
surface (Rectangle x1 y1 x2 y2) = (abs $ x2 - x2) * (abs $ y2 - y1)
```

Here's how that works:

```hs
ghci> surface $ Circle 10 20 10
314.15927
ghci> surface $ Rectangle 0 0 100 100
10000.0
```

We can't print out the circle, until we have it derive show:

```hs
data Shape = Circle Float Float Float | Rectangle Float Float Float Float deriving (Show)
```

Now we can print out the Circle:

```hs
ghci> Circle 10 20 5
Circle 10.0 20.0 5.0
ghci> Rectangle 50 230 60 90
Rectangle 50.0 230.0 60.0 90.0
```

Value constructors are functions, so we can map them and partially apply
them:

```hs
ghci> map (Circle 10 20) [4,5,6,6]
[Circle 10.0 20.0 4.0,Circle 10.0 20.0 5.0,Circle 10.0 20.0 6.0,Circle 10.0 20.0 6.0]
```

Let's make an intermediate Point to simplify our definition:

```hs
data Point = Point Float Float deriving (Show)
data Shape = Circle Point Float | Rectangle Point Point deriving (Show)
```

We can simplify our surface definition now:

```hs
surface :: Shape -> Float
surface (Circle _ r) = pi * r ^ 2
surface (Rectangle (Point x1 y1) (Point x2 y2)) = (abs $ x2 - x1) * (abs $ y2 - y1)
```

Now this works fine.

```hs
ghci> surface (Rectangle (Point 0 0) (Point 100 100))
10000.0
ghci> surface (Circle (Point 0 0) 24)
1809.5574
```

We can add a nudge function to move it around as well:

```hs
nudge :: Shape -> Float -> Float -> Shape
nudge (Circle (Point x y) r) a b = Circle (Point (x+a) (y+b)) r
nudge (Rectangle (Point x1 y1) (Point x2 y2)) a b = Rectangle (Point (x1+a) (y1+b)) (Point (x2+a) (y2+b))
```

```hs
ghci> nudge (Circle (Point 34 34) 10) 5 10
Circle (Point 39.0 44.0) 10.0
```

How about some base constructors?

```hs
baseCircle :: Float -> Shape
baseCircle r = Circle (Point 0 0) r

baseRect :: Float -> Float -> Shape
baseRect width height = Rectangle (Point 0 0) (Point width height)
```

And their use:

```hs
ghci> nudge (baseRect 40 100) 60 23
Rectangle (Point 60.0 23.0) (Point 100.0 123.0)
```

How would we export this?

```hs
module Shapes
( Point(..)
, Shape(..)
, surface
, nudge
, baseCircle
, baseRect
) where
```

## Record Syntax

Here's a data type that describes a person: Their: first name last name
age height phone number favorite ice cream flavor

```hs
data Person = Person String String Int Float String String deriving (Show)
```

It's very cumbersome to use this without labeling them.

```hs
ghci> let guy = Person "Buddy" "Finklestein" 43 184.2 "526-2928" "Chocolate"
ghci> guy
Person "Buddy" "Finklestein" 43 184.2 "526-2928" "Chocolate"
```

Here's how we create value constructors for everything:

```hs
firstName :: Person -> String
firstName (Person firstname _ _ _ _ _) = firstname

lastName :: Person -> String
lastName (Person _ lastname _ _ _ _) = lastname

age :: Person -> Int
age (Person _ _ age _ _ _) = age

height :: Person -> Float
height (Person _ _ _ height _ _) = height

phoneNumber :: Person -> String
phoneNumber (Person _ _ _ _ number _) = number

flavor :: Person -> String
flavor (Person _ _ _ _ _ flavor) = flavor
```

This is a bit painful and difficult to remember, so Haskell provided us
with record syntax:

```hs
data Person = Person {
  firstName :: String
, lastName :: String
, age :: Int
, height :: Float
, phoneNumber :: String
, flavor :: String
} deriving (Show)
```

This also provides us with getters for that person.

So we can do this just like the previous example:

```hs
ghci> let guy = Person "Buddy" "Finklestein" 43 184.2 "526-2928" "Chocolate"ghci> firstName guy
"Buddy"
```

Record syntax is generally preferred when the order of values is vague,
and it's not obvious which field is which.

## Type parameters

A value constructor can take a value (or set of values) of some types
and return a value of a different type.

The Maybe type is defined like this:

```hs
data Maybe a = Nothing | Just a
```

If this type is Null, it returns `Left`, whereas if it holds something,
it returns `Right` which is `Just a`.

Since `Maybe` is generic, it works with any type.

Playing around with that:

```hs
ghci> Just "Haha"
Just "Haha"
ghci> Just 84
Just 84
ghci> :t Just "Haha"
Just "Haha" :: Maybe [Char]
ghci> :t Just 84
Just 84 :: (Num t) => Maybe t
ghci> :t Nothing
Nothing :: Maybe a
ghci> Just 10 :: Maybe Double
Just 10.0
```

This is useful for some type definitions, like Map.

```hs
data (Ord k) => Map k v = ...
```

We can require that the Ord typeclass has to be satisfied for a key, so
the Map can be ordered.

Let's create a Vector 3D vector type and add operations for it. In the
type, don't add the constraint, because we have to for the functions.

```hs
data Vector a = Vector a a a deriving (Show)

vplus :: (Num t) => Vector t -> Vector t -> Vector t
(Vector i j k) `vplus` (Vector l m n) = Vector (i+l) (j+m) (k+n)

vectMult :: (Num t) => Vector t -> t -> Vector t
(Vector i j k) `vectMult` m = Vector (i*m) (j*m) (k*m)

scalarMult :: (Num t) => Vector t -> Vector t -> t
(Vector i j k) `scalarMult` (Vector l m n) = i*l + j*m + k*n
```

## Derived Instances

Typeclasses are more like interfaces with constraints that can be
automatically derived.

```hs
data Person = Person {
firstName :: String
, lastName :: String
, age :: Int
} deriving (Show, Read, Eq)
```

We'll create a person type and then derive Show, Read and Eq for it.

```hs
ghci> let mikeD = Person {firstName = "Michael", lastName = "Diamond", age = 43}
ghci> let adRock = Person {firstName = "Adam", lastName = "Horovitz", age = 41}
ghci> let mca = Person {firstName = "Adam", lastName = "Yauch", age = 44}
ghci> mca == adRock
False
ghci> mikeD == adRock
False
ghci> mikeD == mikeD
True
ghci> mikeD == Person {firstName = "Michael", lastName = "Diamond", age = 43}
True
```

Show is like toString, as it creates a string representation of our
type, whereas read turns a string representation of our type into the
type.

```hs
ghci> read "Person {firstName ="Michael", lastName ="Diamond", age = 43}" :: Person
Person {firstName = "Michael", lastName = "Diamond", age = 43}
```

`Ord` is another typeclass that allows for creating an order.

If we make our `Bool` typeclass like this:

```hs
data Bool = False | True deriving (Ord)
```

We can compare them:

```hs
ghci> True `compare` False
GT
ghci> True > False
True
ghci> True < False
False
```

Likewise, `Maybe` derives `Ord` as well.

```hs
data Maybe a = Nothing | Just a deriving (Ord)
```

```hs
ghci> Nothing < Just 100
True
ghci> Nothing > Just (-49999)
False
ghci> Just 3 `compare` Just 2
GT
ghci> Just 100 > Just 50
True
```

We can use Algebraic Data Types to make enumerations of the `Enum` (a
type with no value constructor), and `Bounded`, which has a lowest
possible value and a highest possible value.

```hs
data Day = Monday | Tuesday | Wednesday | Thursday | Friday | Saturday | Sunday deriving (Eq, Ord, Show, Read, Bounded, Enum)
```

We can use Show and Read:

```hs
ghci> Wednesday
Wednesday
ghci> show Wednesday
"Wednesday"
ghci> read "Saturday" :: Day
Saturday
```

We can use Eq and Ord:

```hs
ghci> Saturday == Sunday
False
ghci> Saturday == Saturday
True
ghci> Saturday > Friday
True
ghci> Monday `compare` Wednesday
LT
```

We can use Bounded:

```hs
ghci> minBound :: Day
Monday
ghci> maxBound :: Day
Sunday
```

We can use succ and Pred and make ranges:

```hs
ghci> succ Monday
Tuesday
ghci> pred Saturday
Friday
ghci> [Thursday .. Sunday]
[Thursday,Friday,Saturday,Sunday]
ghci> [minBound .. maxBound] :: [Day]
[Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday]
```

## Type Synonyms

Remember that the `String` type means `[Char]`.

In Haskell that could be represented like this:

```hs
type String = [Char]
```

Likewise, we could simplify our `Data.Map` module's types:

```hs
phoneBook :: [(String,String)]
phoneBook = [
   (
  ,(
  ,(
  ,(
  ,(
  ,(
  ]
```

We know that this is a mapping of `String` -> `String`, but we could
make a type synonym and make that easier to understand.

```hs
type PhoneNumber = String
type Name = String
type PhoneBook = [(Name,PhoneNumber)]
```

Type synonyms can also be parameterized:

```hs
type AssocList k v = [(k,v)]
```

Let's talk about the `Either` type:

```hs
data Either a b = Left a | Right b deriving (Eq, Ord, Read, Show)
```

We can pattern match Left and Right based on different stuff and see
which one of them it was:

```hs
ghci> Right 20
Right 20
ghci> Left "w00t"
Left "w00t"
ghci> :t Right 'a'
Right 'a' :: Either a Char
ghci> :t Left True
Left True :: Either Bool b
```

## Recursive Data Structures

Let's make a List data type with Algebraic Data Types

```hs
data List a = Empty | Cons a (List a) deriving (Show, Read, Eq, Ord)
```

`Cons` is the `:` operator. Therefore, these are the same:

```hs
ghci> 4 `Cons` (5 `Cons` Empty)
[4,5]
ghci> 4: (5 : [])
[4,5]
```

We can also define how high the precedence is of our operator `:-:`.

```hs
infixr 5 :-:
data List a = Empty | a :-: (List a) deriving (Show, Read, Eq, Ord)
```

Let's define our own `++` operator:

```hs
infixr 5  .++
(.++) :: List a -> List a -> List a
Empty .++ ys = ys
(x :-: xs) .++ ys = x :-: (xs .++ ys)
```

Let's make a binary search tree:

```hs
data Tree a = EmptyTree | Node a (Tree a) (Tree a) deriving (Show, Read, Eq)
```

Here are two functions: One makes a singleton tree, and another one
makes a function to insert an element into a tree.

```hs
singleton :: a -> Tree a
singleton x = Node x EmptyTree EmptyTree

treeInsert :: (Ord a) => a -> Tree a -> Tree a
treeInsert x EmptyTree = singleton x
treeInsert x (Node a left right)
  | x == a = Node x left right
  | x < a  = Node a (treeInsert x left) right
  | x > a  = Node a left (treeInsert x right)
```

Here's a function that checks if an Element is in a tree:

```hs
treeElem :: (Ord a) => a -> Tree a -> Bool
treeElem x EmptyTree = False
treeElem x (Node a left right)
  | x == a = True
  | x < a = treeElem x left
  | x > a = TreeElem x right
```

And let's start inserting values into the tree:

```hs
ghci> let nums = [8,6,4,1,7,3,5]
ghci> let numsTree = foldr treeInsert EmptyTree nums
ghci> numsTree
Node 5 (Node 3 (Node 1 EmptyTree EmptyTree) (Node 4 EmptyTree EmptyTree)) (Node 7 (Node 6 EmptyTree EmptyTree) (Node 8 EmptyTree EmptyTree))
```

## Typeclasses 102

Let's see how the `Eq` typeclass is implemented:

```hs
class Eq a where
  (==) :: a -> a -> Bool
  (/=) :: a -> a -> Bool
  x == y = not (x /= y)
  x /= y = not (x == y)
```

A type conforms to the `Eq` typeclass if it has a definition for `==`
and `/=` and doesn't have the same implementation for `==` and `/=`.

Let's write a Traffic Light class:

```hs
data TrafficLight = Red | Yellow | Green
```

Normally we could derive it automatically, but let's write it out:

```hs
instance Eq TrafficLight where
  Red == Red = True
  Green == Green = True
  Yellow == Yellow = True
  _ == _ = False
```

Because `Eq` is defined in terms of each other, we can stop right here.
`Eq` is fulfilled, because it can figure out the definition for `/=`.

Here's how show would be written by hand:

```hs
instance Show TrafficLight where
    show Red = "Red light"
    show Yellow = "Yellow light"
    show Green = "Green light"
```

Let's override `Eq` for `Maybe`.

```hs
instance (Eq m) => Eq (Maybe m) where
  Just x == Just y = x == y
  Nothing == Nothing = True
  _ == _ = False
```

## Functors

The functor typeclass allows you to use a function on every instance of
something:

fmap is the defined like this:

```hs
class Functor f where
  fmap :: (a -> b) -> f a -> f b
```

Prev:
[learn-you-a-haskell-chapter-7](learn-you-a-haskell-chapter-7.md)
Next:
[learn-you-a-haskell-chapter-9](learn-you-a-haskell-chapter-9.md)
