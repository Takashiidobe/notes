---
title: HyperLogLogs
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Monday, February 24th 2025, 7:24:28 am
---

# HyperLogLogs

Ever wanted to count how many unique items you had in a collection? I
have. Ever wanted to count how many unique items you had in a collection
without having to allocate O(n) memory? I have.

For that we have to sacrifice some accuracy, but it\'s well worth it.

Imagine we have a large csv file with a number per line, and it\'s got a
bunch of random numbers in it, and we\'re tasked with counting how many
numbers are unique in the csv.

Easy peasy, you\'re probably thinking. Just use a set.

Let\'s do it in python.

```python
with open(input_file) as f:
    unique_nums = {line.rstrip() for line in f}
    print(len(unique_nums))
```

Lemon squeezy. But this taks O(n) time and O(n) memory. So what happens
if our generated csv has like a billion elements? Well, my computer runs
out of memory generating the CSV and then runs out memory trying to
parse it this way. We\'re going to need to find another way. One that
doesn\'t store the entire number in memory while we iterate through
it\...

Enter the HyperLogLog! It probablistically finds the number of unique
items in a set.

Like most efficient things in programming, this starts out by hashing
our values. Python is a great language for this (as are a few others)
because it comes with a hash method you can easily call!

First we\'ll define a function that defines the number of trailing
zeroes a number hasin its binary representation:

```python
def trailing_zeroes(num):
    if num == 0:
        return 32
    z = 0
    while (num >> z) & 1 == 0:
        z += 1
    return z
```

Nice. We\'re going to use this to find out about how many elements are
in a set. Let\'s say I ask you to flip a coin, and tell me the maximum
amount of times in a row you got heads.

If you say 1, I\'m going to guess 2. If you say 2, I\'m going to guess 4. If you say 3, I\'m going to guess 8. If you say 4, I\'m going to
guess 16.

Since there is a 50% chance of getting 1 heads, that means on average,
in 2 coin flips, you will get to 1 head in a row. Likewise, you can get
to 2 heads in a row in 4 coin flips, and 3 in 8.

If you write the numbers of 0 to 15 in binary, you\'ll get this. Notice
that this tells us exactly the average chance of how many heads we have
in a row; to get 4 heads in a row (1111), we\'ll flip on average 16
coins (the base 10 version of 1111). Because of this, we can guess about
how many unique items are in the set by seeing the longest number of 0s
or 1s we see in our hashed set. Interesting, right?

0000 0100 1000 1100

---

0001 0101 1001 1101
0010 0110 1010 1110
0100 0111 1011 1111

So all we have to do is hash the items and count the longest sequence.
Let\'s do that, but with some errors removed.

```python
def estimate_cardinality(values, k=10):
    buckets = 2 ** k
    max_zeroes = [0] * buckets
    for value in values:
        h = hash(value)
        bucket = h & (buckets - 1)
        bucket_hash = h >> k
        max_zeroes[bucket] = max(
            max_zeroes[bucket], trailing_zeroes(bucket_hash)
        )
```

And let\'s run it.

```python
lines = None
with open(input_file) as f:
    lines = [line.rstrip() for line in f]

uniques = estimate_cardinality(lines)

print(f)
```

I ran this on my computer with a million numbers in a csv, randomly
generated from 1 to 1 million and I got an error rate of 5.7% compared
to the previous set. With increased buckets, I got it down to 3%. And
I\'m basically using 5% of the memory of the previous solution, which
isn\'t anything to scoff at. A great way to count unique items with less
memory! 
