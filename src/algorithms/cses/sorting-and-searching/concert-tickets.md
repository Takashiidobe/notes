---
title: concert-tickets
---

Tickets\"

# Concert Tickets

Prev: \[ferris-wheel](ferris-wheel.md) Next:
\[restaurant-customers](restaurant-customers.md)

There are n concert tickets available, each with a certain price. Then,
m customers arrive, one after another.

Each customer announces the maximum price he or she is willing to pay
for a ticket, and after this, they will get a ticket with the nearest
possible price such that it does not exceed the maximum price.

Input

The first input line contains integers n and m: the number of tickets
and the number of customers.

The next line contains n integers h1,h2,\...,hn: the price of each
ticket.

The last line contains m integers t1,t2,\...,tm: the maximum price for
each customer.

Output

Print, for each customer, the price that they will pay for their ticket.
After this, the ticket cannot be purchased again.

If a customer cannot get any ticket, print −1.

## Explanation

We can do this like we did the apartments problem, by sorting both the
concert tickets and the customers and incrementing both if we have a
match, incrementing the customers if the ticket price is too high, and
vice versa.

Or we can use a sorted map, and not sort the customer prices.

For every customer want, we want to find the next lowest price in the
map. If we can\'t find it, we\'ll print out -1, otherwise, we\'ll print
the price we found and erase that price from the map and move on.

## Solution

Prev: \[ferris-wheel](ferris-wheel.md) Next:
\[restaurant-customers](restaurant-customers.md)
