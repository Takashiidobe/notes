---
title: calculate-best-discount
---

Best Discount\"

# Question

We want to give the customer the biggest discount we can for the money
they have.

Let\'s assume you\'re given a list of discount prices for a set of
items, and a list of normal pricing for a set of items. As well, your
client has given you a certain amount of money that you will allocate
first to discount prices for items, and you\'re given a list of items
and the count that of it that they bought.

## Approach

First, calculate the discount pricing for each item. We can assume that
all items in the purchase list are a subset of items in the discount
price list and normal pricing list. We\'ll call that the ratioed_prices
and then sort by that \-- we can use a heap here.
