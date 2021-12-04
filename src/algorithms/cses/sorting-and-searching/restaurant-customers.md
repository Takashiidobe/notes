---
title: restaurant-customers
---

Customers\"

# Restaurant Customers

Prev: \[concert-tickets](concert-tickets.md) Next:
\[movie-festival](movie-festival.md)

You are given the arrival and leaving times of n customers in a
restaurant.

What was the maximum number of customers?

Input

The first input line has an integer n: the number of customers.

After this, there are n lines that describe the customers. Each line has
two integers a and b: the arrival and leaving times of a customer.

You may assume that all arrival and leaving times are distinct.

Output

Print one integer: the maximum number of customers.

## Explanation

With the assumption that all entering and leaving times are distinct, we
can sort this to find a greedy answer.

First, we\'ll create a vector of pairs\<int, bool>. For every time we
see, we\'ll push back once for {enter_time, true} and leaving_time,
false}, and sort the vector.

Then, we\'ll count the maximum customers we\'ve seen so far and the
current customer count.

We\'ll iterate through the vector; if the right hand side says true, we
know a customer has entered. Increment the current customer count, and
update the maximum customers found if we hit a new max. Otherwise, if
the right hand side says false, we know a customer has left. Decrement
the current customer count.

## Solution

```cpp
{{# include _include/code/algorithms/cses/cpp/sorting-and-searching/restaurant-customers.cc }}
```

Prev: \[concert-tickets](concert-tickets.md) Next:
\[movie-festival](movie-festival.md)
