---
title: "Counting Large Numbers of Events in Small Registers"
---

Morris wanted to count large numbers in a computer with 8-bit registers.
He goes through some simple methods first:

## 0% Error

To get 0% error, you can count up to 2^n - 1, so 8-bits can count to 255.
This is pretty small.

## Simple Solution

To get a simple solution, you can flip a coin at every event to check
whether or not it should count. This causes an error of n / 2, where n
is the count of events and the standard deviation is the root of v / 2.

The error for this grows with the root of the number, so for small
numbers, the standard deviation is very high (if the counter is 9, the
number is between 6 and 12 most of the time, which is high).

## The Solution

Instead of doing this, we can find an optimal solution by having the
register only store the power of the event.

Let's take 101, which is 5. To calculate the estimated value, it is 2^5 or 32.

To increment from 4 to 8, a psuedo-random number would be generated such
that a probability of .25 generates a positive change in the counter.
So, roughly every 4 times, it increments the counter. Then, when it
becomes 8, you halve this probability, making it so that 1/8th every
increment, the counter is incremented. (You can also decrement with this).

This has logarithmically scaling error, so it's pretty good.

An example program for this in C:

```c
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    puts("Please provide a number to approximately count to");
    exit(1);
  }

  uint64_t increment_count = atoi(argv[1]);
  uint8_t counter = 0;

  for (int i = 0; i < increment_count; i++) {
    uint32_t rand_num = arc4random_uniform(1 << (counter + 1));
    if (rand_num == counter) {
      counter++;
    }
  }

  printf("incremented %llu times, counter is: %llu\n", increment_count, (uint64_t) 1 << counter);
}
```
