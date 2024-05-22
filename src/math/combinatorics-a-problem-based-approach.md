# Combinatorics a Problem Based Approach

## Chapter 1

1.1. A die is thrown five times. The experiment results in a sequence
$c_1c_2c_3c_4c_5$, where $c_i \in \{1, 2, \ldots, 6\}$ is a positive
integer obtained in the $i$-th throw. How many distinct results are there?

This is $6 ^ 5$ or 7776.

1.2. How many four-digit even positive integers are there without a repetition of the digits?

This is done with the inclusion-exclusion principle.

A number must either be even or odd, and there should be an equal (or
off by one number of them.

So there are:
9 choices for the first digit (1-9, zero is not allowed)
10 choices for the second digit (0-9)
10 choices for the third digit (0-9)
10 choices for the last digit (0-9)

Thus, there are 9000 even or odd numbers. We know half should be even
and half should be odd, so 4500 even numbers.

1.3. How many functions $f : \{1, 2, 3, 4\} \to \{a, b, c\}$ are there?

The domain has 4 elements
The codomain has 3 elements

This can be reduced to $3^4$, the length of the codomain to the power of
the length of the domain.

So $3^4$ or $81$.

1.4. How many onto functions $f : \{1, 2, 3, 4\} \to \{a, b, c\}$ are there?

The domain has 4 elements
The codomain has 3 elements

We take the previous answer, 81, and then remove all non-onto functions.

There are 48 functions missing one element.
However, this also includes 3 extra functions which are to be added in.

So $81 - 48 + 3 \equals 36$.

1.5. How many functions $f : \{1, 2, \ldots, n\} \to \{1, 2\}$ are there

The domain has n elements
The codomain has 2 elements

Thus, $2^n$ functions.

1.6. How many ten-digit positive integers are there such that all of the
following conditions are satisfied:
a. Each of the digits $\{0, 1, \dots, 9\}$ appears exactly once;
b. The first digit is odd;
c. Five even digits appear in five consecutive positions?

Following the conditions:

The first digit has 5 odd digits available, so $5 *
(rest_of_conditions)$
The five consecutive even digits take up 5 slots and can start from
position 1 through 5, and there are $5!$ ways to arrange it, so $5 *
5!$.
There are four remaining possible digits, which can be arranged in $4!$
ways.

So the answer is $5 * 5 * 5! * 4!$ or 72000.

## Chapter 2

2.1. How many 3-digit positive integers are there, such that three distinct
digits appear in the decimal representation of any of them?

This is $9 * 9 * 9$ or 648 because 1-9 are valid digits and there are
three of them, so they multiply.

2.2. How many 5-digits positive integers are there that are divisible by 5
and without a repetition of digits?

The last digit can either be 0 or 5.

In the case the last digit is 0,

There are $9 * 8 * 7 * 6$ or 3024 choices.

In the case the last digit is 5,

There are $8 * 8 * 7 * 6$ or 2688 choices.

Add these up to get 5712. The answer in the textbook is wrong.

2.3. Twelve basketball teams take part in a tournament. How many possible
ways are there for the distribution of gold, silver, and bronze medals?

There are 12 choices for the gold, 11 for the silver, and 10 for the
bronze, so $12 * 11 * 10$ or 1320.

2.4. There are n light bulbs in a room, each of them with its own switch.
How many ways can the room be lighted?

This is a bit counting problem, so $2^n$.
