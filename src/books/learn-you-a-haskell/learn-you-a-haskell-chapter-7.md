---
title: learn-you-a-haskell-chapter-7
---

You A Haskell Chapter 7

# Modules

We can import modules by using the `import` keyword.

```hs
import Data.List
numUniques :: (Eq a) => [a] -> Int
numUniques = length . nub
```

To import in GHCI:

```hs
ghci> :m + Data.List
```

To import a set of modules in GHCI:

```hs
ghci> :m + Data.List Data.Map Data.Set
```

To import only a few parts of a module:

```hs
import Data.List (nub, sort)
```

To import everything except something:

```hs
import Data.List hiding(nub)
```

We can import qualified as well, which requires typing out the full
name:

```hs
import qualified Data.Map
```

We can rename it with `as`.

```hs
import qualified Data.Map as M
```

## Data.List

`intersperse` takes an element and a list and puts that element in
between each pair of elements in that list.

```hs
ghci> intersperse '.' "MONKEY"
"M.O.N.K.E.Y"
ghci> intersperse 0 [1,2,3,4,5,6]
[1,0,2,0,3,0,4,0,5,0,6]
```

`intercalate` takes a list of lists and a list and inserts that element
between those lists and flattens the lists.

```hs
ghci> intercalate " " ["hey","there","guys"]
"hey there guys"
ghci> intercalate [0,0,0] [1,2,3],[4,5,6],[7,8,9]]
[1,2,3,0,0,0,4,5,6,0,0,0,7,8,9]
```

`transpose` transposes a list of lists. The columns become the rows and
the rows become the columns.

```hs
ghci> transpose [1,2,3],[4,5,6],[7,8,9]]
[1,4,7],[2,5,8],[3,6,9]]
ghci> transpose ["hey","there","guys"]
["htg","ehu","yey","rs","e"]
```

Let\'s say we have some list where we want to sum up column-wise.

We can do this:

```hs
map sum $ transpose [0,3,5,9],[10,0,0,9],[8,5,1,-1]]
[18,8,6,17]
```

`foldl'` and `foldll'` are the strict versions of `foldl` and `foldll`.
Instead of returning a `thunk`, they calculate intermediate values,
which lets them be more effective.

`concat` flattens a list of lists into a list of elements one level.

```hs
ghci> concat ["foo","bar","car"]
"foobarcar"
ghci> concat [3,4,5],[2,3,4],[2,1,1]]
[3,4,5,2,3,4,2,1,1]
```

`concatMap` is the same as first mapping a function to a list and then
concatenating the list with `concat`.

```hs
ghci> concatMap (replicate 4) [1..3]
[1,1,1,1,2,2,2,2,3,3,3,3]
```

`and` takes a list of boolean values and returns `True` only if all the
values in the list are `True`.

```hs
ghci> and $ map (>4) [5,6,7,8]
True
ghci> and $ map (==4) [4,4,4,3,4]
False
```

`or` is like `and`, only it returns true if any of the boolean values is
`True`.

```hs
ghci> or $ map (==4) [2,3,4,5,6,1]
True
ghci> or $ map (>4) [1,2,3]
False
```

`any` and `all` work as you would expect, checking if all conform or any
conform.

```hs
ghci> any (==4) [2,3,5,6,1,4]
True
ghci> all (>4) [6,9,10]
True
ghci> all (`elem` ['A'..'Z']) "HEYGUYSwhatsup"
False
ghci> any (`elem` ['A'..'Z']) "HEYGUYSwhatsup"
True
```

`iterate` takes a function and a starting value. It applies the function
to the starting value, then it applies that function to the result
infinitely.

```hs
ghci> take 10 $ iterate (*2) 1
[1,2,4,8,16,32,64,128,256,512]
ghci> take 3 $ iterate (++  "haha"
["haha","hahahaha","hahahahahaha"]
```

`splitAt` takes a number and a list. It splits the list at that many
elements, returns a tuple.

```hs
ghci> splitAt 3 "heyman"
(
ghci> splitAt 100 "heyman"
(
ghci> splitAt (-3) "heyman"
(
ghci> let (a,b) = splitAt 3 "foobar" in b ++ a
"barfoo"
```

`takeWhile` takes elements from a list while the predicate is true.

```hs
ghci> takeWhile (>3) [6,5,4,3,2,1,2,3,4,5,4,3,2,1]
[6,5,4]
ghci> takeWhile (/=' ') "This is a sentence"
"This"
```

What if we wanted to know the sum of all third powers that are under
10,000?

We can do something like this:

We make an infinite list of third powers, chop them off when they\'re
greater than 10000, then sum them.

```hs
ghci> sum $ takeWhile (<10000) $ map (^3) [1..]
53361
```

`dropWhile` only drops elements while the predicate is true. Once it
becomes False, it returns the rest of the list.

```hs
ghci> dropWhile (/= ' ') "This is a sentence"
" is a sentence"
ghci> dropWhile (<3) [1,2,2,2,3,4,5,4,3,2,1]
[3,4,5,4,3,2,1]
```

Imagine finding out when the stock value of a stock exceeds \$1000.

```hs
ghci> let stock = [(994.4,2008,9,1),(995.2,2008,9,2),(999.2,2008,9,3),(1001.4,2008,9,4),(998.3,2008,9,5)]
ghci> head (dropWhile (\(val,y,m,d) -> val < 1000) stock)
(1001.4,2008,9,4)
```

`span` is like `takeWhile`, only it returns a pair of lists.

```hs
ghci> let (fw, rest) = span (/=' ') "This is a sentence" in "First word:" ++ fw ++ ", the rest:" ++ rest
"First word: This, the rest: is a sentence"
```

`break` is the opposite, it splits when the predicate is first true.

```hs
ghci> break (==4) [1,2,3,4,5,6,7]
([1,2,3],[4,5,6,7])
ghci> span (/=4) [1,2,3,4,5,6,7]
([1,2,3],[4,5,6,7])
```

`sort` sorts a list. They must conform to `Ord` to be sortable.

```hs
ghci> sort [8,5,3,2,1,6,4,2]
[1,2,2,3,4,5,6,8]
ghci> sort "This will be sorted soon"
"    Tbdeehiillnooorssstw"
```

`group` takes a list and groups adjacent elements into sublists if they
are equal.

```hs
ghci> group [1,1,1,1,2,2,2,2,3,3,2,2,2,5,6,7]
[1,1,1,1],[2,2,2,2],[3,3],[2,2,2],[5],[6],[7]]
```

We can sort and map to find out how many times each element appears in
the list.

```hs
ghci> map (\l@(x:xs) -> (x,length l)) . group . sort $ [1,1,1,1,2,2,2,2,3,3,2,2,2,5,6,7]
[(1,4),(2,7),(3,2),(5,1),(6,1),(7,1)]
```

`inits` and `tails` are like `init` and `tail`, but they apply
recursively until there\'s nothing left.

```hs
ghci> inits "w00t"
["","w","w0","w00","w00t"]
ghci> tails "w00t"
["w00t","00t","0t","t",""]
ghci> let w = "w00t" in zip (inits w) (tails w)
[(]
```

`isInfixOf` searches for a sublist inside a list and returns `True` if
the sublist we\'re looking for is somewhere inside the target list.

```hs
ghci> "cat" `isInfixOf` "im a cat burglar"
True
ghci> "Cat" `isInfixOf` "im a cat burglar"
False
ghci> "cats" `isInfixOf` "im a cat burglar"
False
```

`isPrefixOf` and `isSuffixOf` check for a sublist at the beginning and
end of a list.

```hs
ghci> "hey" `isPrefixOf` "hey there!"
True
ghci> "hey" `isPrefixOf` "oh hey there!"
False
ghci> "there!" `isSuffixOf` "oh hey there!"
True
ghci> "there!" `isSuffixOf` "oh hey there"
False
```

`elem` and `notElem` takes a list and a predicate and returns a pair of
lists.

The first list in the result contains all the elements that satisfy the
predicate, the second one contains all the ones that don\'t.

```hs
ghci> partition (`elem` ['A'..'Z']) "BOBsidneyMORGANeddy"
(
ghci> partition (>3) [1,3,5,6,3,2,1,0,3,7]
([5,6,7],[1,3,3,2,1,0,3])
```

`partition` takes a list and a predicate and returns a pair of lists.
The first list in the result contains all the elements that satisfy the
predicate, while the second one contains all the ones that don\'t.

```hs
ghci> partition (`elem` ['A'..'Z']) "BOBsidneyMORGANeddy"
(
ghci> partition (>3) [1,3,5,6,3,2,1,0,3,7]
([5,6,7],[1,3,3,2,1,0,3])
```

`find` takes a list and a predicate and returns the first element that
satisfies the predicate.

It returns this in a `Maybe` type, as the value can be `Just something`
or `Nothing`.

```hs
ghci> find (>4) [1,2,3,4,5,6]
Just 5
ghci> find (>9) [1,2,3,4,5,6]
Nothing
ghci> :t find
find :: (a -> Bool) -> [a] -> Maybe a
```

`elemIndex` is like `elem`, but it returns a `Maybe` with the index.

```hs
ghci> 4 `elemIndex` [1,2,3,4,5,6]
Just 3
ghci> 10 `elemIndex` [1,2,3,4,5,6]
Nothing
```

`elemIndices` returns a list of indices where the element may crop up.

```hs
ghci> ' ' `elemIndices` "Where are the spaces?"
```

`findIndex`/ `findIndices` returns the index/indices that match.

```hs
ghci> findIndex (==4) [5,3,2,1,6,4]
Just 5
ghci> findIndex (==7) [5,3,2,1,6,4]
Nothing
ghci> findIndices (`elem` ['A'..'Z']) "Where Are The Caps?"
[0,6,10,14]
```

There\'s `zip3`, `zipWith3`, for when you want to zip three lists or
apply a function to a zip.

`lines` deals with files and takes a string and returns every line of
that string in a separate list.

```hs
ghci> lines "first line\nsecond line\nthird line"
["first line","second line","third line"]
```

`unlines` is the inverse of `lines`. It takes a list of strings and
merges them using \'\\n\'.

```hs
ghci> unlines ["first line", "second line", "third line"]
"first line\nsecond line\nthird line\n"
```

`words` and `unwords` are for splitting a line of text into words or
joining a list of words into a text.

```hs
ghci> words "hey these are the words in this sentence"
["hey","these","are","the","words","in","this","sentence"]
ghci> words "hey these           are    the words in this\nsentence"
["hey","these","are","the","words","in","this","sentence"]
ghci> unwords ["hey","there","mate"]
"hey there mate"
```

`nub` returns the unique elements of a list.

```hs
ghci> nub [1,2,3,4,3,2,1,2,3,4,3,2,1]
[1,2,3,4]
ghci> nub "Lots of words and stuff"
"Lots fwrdanu"
```

`delete` takes an element and a list and deletes the first occurence of
that element in the list.

```hs
ghci> [1..10] \\ [2,5,9]
[1,3,4,6,7,8,10]
ghci> "Im a big baby" \\ "big"
"Im a  baby"
```

`union` appends every element that doesn\'t appear in \$f1 to it.

```hs
ghci> "hey man" `union` "man what's up"
"hey manwt'sup"
ghci> [1..7] `union` [5..10]
[1,2,3,4,5,6,7,8,9,10]
```

`intersect` works like set intersection.

```hs
[1..7] `intersect` [5..10]
```

`insert` takes an element and a list of elements and inserts it into a
position where it\'s still less than or equal to the next element.

```hs
ghci> insert 4 [3,5,1,2,8,2]
[3,4,5,1,2,8,2]
```

`insert` on a sorted list keeps it sorted.

```hs
ghci> insert 4 [1,2,3,5,6,7]
[1,2,3,4,5,6,7]
ghci> insert 'g' $ ['a'..'f'] ++ ['h'..'z']
"abcdefghijklmnopqrstuvwxyz"
ghci> insert 3 [1,2,4,3,2,1]
[1,2,3,4,3,2,1]
```

genericLength, genericTake, genericDrop, genericSplitAt, genericIndex
and genericReplicate are generic functions.

if you want to provide a function as a comparator, we have nubBy,
deleteBy, unionBy, intersectBy and groupBy.

if we import `on` from `Data.Function`, we can split values on a group
like this:

```hs
ghci> groupBy ((==) `on` (> 0)) values
[-4.3,-2.4,-1.2],[0.4,2.3,5.9,10.5,29.1,5.3],[-2.4,-14.5],[2.9,2.3]]
```

`on` is used a lot with `By` functions.

```hs
ghci> let xs = [5,4,5,4,4],[1,2,3],[3,5,4,3],[],[2],[2,2]]
ghci> sortBy (compare `on` length) xs
[],[2],[2,2],[1,2,3],[3,5,4,3],[5,4,5,4,4]]
```

## Data.Char

isControl checks whether a character is a control character.

isSpace checks whether a character is a white-space characters. That
includes spaces, tab characters, newlines, etc.

isLower checks whether a character is lower-cased.

isUpper checks whether a character is upper-cased.

isAlpha checks whether a character is a letter.

isAlphaNum checks whether a character is a letter or a number.

isPrint checks whether a character is printable. Control characters, for
instance, are not printable.

isDigit checks whether a character is a digit.

isOctDigit checks whether a character is an octal digit.

isHexDigit checks whether a character is a hex digit.

isLetter checks whether a character is a letter.

isMark checks for Unicode mark characters. Those are characters that
combine with preceding letters to form letters with accents. Use this if
you are French.

isNumber checks whether a character is numeric.

isPunctuation checks whether a character is punctuation.

isSymbol checks whether a character is a fancy mathematical or currency
symbol.

isSeparator checks for Unicode spaces and separators.

isAscii checks whether a character falls into the first 128 characters
of the Unicode character set.

isLatin1 checks whether a character falls into the first 256 characters
of Unicode.

isAsciiUpper checks whether a character is ASCII and upper-case.

isAsciiLower checks whether a character is ASCII and lower-case.

Data.Char also exports GeneralCategory, which is like ordering, but it
has 31 categories, like Space, UppercaseLetter, LowercaseLetter,
OtherPunctuation, DecimalNumber.

toUpper converts a character to upper-case. Spaces, numbers, and the
like remain unchanged.

toLower converts a character to lower-case.

toTitle converts a character to title-case. For most characters,
title-case is the same as upper-case.

digitToInt converts a character to an Int. To succeed, the character
must be in the ranges \'0\'..\'9\', \'a\'..\'f\' or \'A\'..\'F\'.

intToDigit is the inverse function of digitToInt. It takes an Int in the
range of 0..15 and converts it to a lower-case character.

The ord and chr functions convert characters to their corresponding
numbers and vice versa:

## Data.Map

To use `Data.Map`, we import it:

```hs
import qualified Data.Map as Map
```

`fromList` takes an association list and returns a map.

```hs
ghci> Map.fromList [(]
fromList [(]
ghci> Map.fromList [(1,2),(3,4),(3,2),(5,5)]
fromList [(1,2),(3,2),(5,5)]
```

Duplicate keys are discarded.

`empty` represents an empty map.

`insert` takes a key, a value and a map and returns a new map, but
inserts the key and value to the map.

```hs
ghci> Map.empty
fromList []
ghci> Map.insert 3 100 Map.empty
fromList [(3,100)]
ghci> Map.insert 5 600 (Map.insert 4 200 ( Map.insert 3 100  Map.empty))
fromList [(3,100),(4,200),(5,600)]
ghci> Map.insert 5 600 . Map.insert 4 200 . Map.insert 3 100 $ Map.empty
fromList [(3,100),(4,200),(5,600)]
```

`null` checks if a map is empty.

```hs
ghci> Map.null Map.empty
True
ghci> Map.null $ Map.fromList [(2,3),(5,5)]
False
```

`size` reports the size of a map.

```hs
ghci> Map.size Map.empty
0
ghci> Map.size $ Map.fromList [(2,4),(3,3),(4,2),(5,4),(6,4)]
5
```

`singleton` takes a key and a value and creates a map with exactly one
mapping.

```hs
ghci> Map.singleton 3 9
fromList [(3,9)]
ghci> Map.insert 5 9 $ Map.singleton 3 9
fromList [(3,9),(5,9)]
```

`lookup` returns a `Maybe`, searching for the value through a key.

`member` takes a value and returns a boolean if the key is in the map or
not.

```hs
ghci> Map.member 3 $ Map.fromList [(3,6),(4,3),(6,9)]
True
ghci> Map.member 3 $ Map.fromList [(2,5),(4,5)]
False
```

`map` and `filter` work like a list.

`toList` turns a map to a list.

`keys` and `elems` return lists of keys and values.

`fromListWith` uses a function supplied to it to decide what to do with
them.

```hs
 phoneBook =
    [(
    ,(
    ,(
    ,(
    ,(
    ,(
    ,(
    ,(
    ,(
    ,(
    ]
```

```hs
phoneBookToMap :: (Ord k) => [(k, String)] -> Map.Map k String
phoneBookToMap xs = Map.fromListWith (\number1 number2 -> number1 ++ ", " ++ number2) xs
```

```hs
ghci> Map.lookup "patsy" $ phoneBookToMap phoneBook
"827-9162, 943-2929, 493-2928"
ghci> Map.lookup "wendy" $ phoneBookToMap phoneBook
"939-8282"
ghci> Map.lookup "betty" $ phoneBookToMap phoneBook
"342-2492, 555-2938"
```

We can break ties with a function:

```hs
ghci> Map.fromListWith max [(2,3),(2,5),(2,100),(3,29),(3,22),(3,11),(4,22),(4,15)]
fromList [(2,100),(3,29),(4,22)]
```

We can break ties by adding values:

```hs
ghci> Map.fromListWith (+) [(2,3),(2,5),(2,100),(3,29),(3,22),(3,11),(4,22),(4,15)]
fromList [(2,108),(3,62),(4,37)]
```

`insertWith` passes in a function to break ties on a map.

```hs
ghci> Map.insertWith (+) 3 100 $ Map.fromList [(3,4),(5,103),(6,339)]
fromList [(3,104),(5,103),(6,339)]
```

## Data.Set

```hs
import qualified Data.Set as Set
```

Set is like map. We turn lists to sets using `Set.fromList`.

We can use `intersection`, `difference`, `union`, `null`, `size`,
`member`, `empty`, `singleton`, `insert`, and `delete` like you would
expect.

or we can `map` or `filter`.

## Making our own Modules

Let\'s make our own module, `Geometry.hs`.

```hs
module Geometry
( sphereVolume
, sphereArea
, cubeVolume
, cubeArea
, cuboidArea
, cuboidVolume
) where

sphereVolume :: Float -> Float
sphereVolume radius = (4.0 / 3.0) * pi * (radius ^ 3)

sphereArea :: Float -> Float
sphereArea radius = 4 * pi * (radius ^ 2)

cubeVolume :: Float -> Float
cubeVolume side = cuboidVolume side side side

cubeArea :: Float -> Float
cubeArea side = cuboidArea side side side

cuboidVolume :: Float -> Float -> Float -> Float
cuboidVolume a b c = rectangleArea a b * c

cuboidArea :: Float -> Float -> Float -> Float
cuboidArea a b c = rectangleArea a b * 2 + rectangleArea a c * 2 + rectangleArea c b * 2

rectangleArea :: Float -> Float -> Float
rectangleArea a b = a * b
```

We can import this module in the same folder like this:

`import Geometry`.

We could split this up into three modules, by placing them in a
`Geometry` folder and making three different files.

`Sphere.hs`

```hs
module Geometry.Sphere
( volume
, area
) where

volume :: Float -> Float
volume radius = (4.0 / 3.0) * pi * (radius ^ 3)

area :: Float -> Float
area radius = 4 * pi * (radius ^ 2)
```

`Cuboid.hs`

```hs
module Geometry.Cuboid
( volume
, area
) where

volume :: Float -> Float -> Float -> Float
volume a b c = rectangleArea a b * c

area :: Float -> Float -> Float -> Float
area a b c = rectangleArea a b * 2 + rectangleArea a c * 2 + rectangleArea c b * 2

rectangleArea :: Float -> Float -> Float
rectangleArea a b = a * b
```

`Cube.hs`

```hs
module Geometry.Cube
( volume
, area
) where

import qualified Geometry.Cuboid as Cuboid

volume :: Float -> Float
volume side = Cuboid.volume side side side

area :: Float -> Float
area side = Cuboid.area side side side
```

And importing like so:

```hs
import qualified Geometry.Sphere as Sphere
import qualified Geometry.Cuboid as Cuboid
import qualified Geometry.Cube as Cube
```

Prev:
\[learn-you-a-haskell-chapter-6](learn-you-a-haskell-chapter-6.md)
Next:
\[learn-you-a-haskell-chapter-8](learn-you-a-haskell-chapter-8.md)
