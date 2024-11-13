---
title: Combinatorics a Problem Based Approach
date created: Thursday, May 23rd 2024, 11:21:47 am
date modified: Tuesday, November 12th 2024, 8:30:16 pm
---
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

So $81 - 48 + 3 = 36$.

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

2.5. (a) How many divisors of natural number 2000 are there?
(b) Let $p_1, p_2, \ldots, p_m$ be distinct prime numbers, and
$k_1, k_2, \ldots, k_m$ be positive integers. Determine the number of
divisors of the positive integer $n = p_1^{k_1} p_2^{k_2} \ldots p_m^{k_m}$.

To find the divisors of 2000, we calculate its prime factorization:

$2^4 * 5^3$. Then we take the exponents of all the factors and add one
to them and multiply them:

So we get $(4 + 1)(3 + 1)$ or 20.

This generalizes to all positive integers.

2.6. Determine all positive integers with an odd number of divisors.

All perfect squares have an odd number of divisions, so the set of $N *
N$.

2.7. In a big country no two citizens have the same arrangement of teeth.
What is the maximal possible number of citizens in this country?

This should be $2^n$ where n is the number of the teeth every citizen has.

2.8. Let $n \geq 2$. How many permutations of the set $\{1, 2, \ldots, n\}$ are there, such that 1 and 2 are adjacent terms?

You can have n - 1 arrangements of (1, 2) in n items. Since they can go
in any spot, there are $(n - 1)!$ ways to do so.
We double this for the reverse (2, 1):
$2(n - 1)!$

2.9. Let $n \geq 2$. How many permutations of the set $\{1, 2, \ldots, n\}$ are there,
such that 2 is placed after 1, not necessarily at adjacent positions?

2.10. Let $n \geq k + 2$. How many permutations of the set $\{1, 2, \ldots, n\}$ are there,
such that exactly $k$ elements appear between 1 and 2?

2.11. How many permutations $(a_1, a_2, \ldots, a_{3n})$ of the set
$\{1, 2, \ldots, 3n\}$ are there, such that, for any $k \in \{1, 2, \ldots, 3n\}$,
the difference $k - a_k$ is divisible by 3?

2.12. How many ways can eight white chess pieces
(the king, the queen, two rooks, two knights, and two bishops)
be arranged on the first row of a chessboard?

The general formula for solving this would look like this:

$$
\frac{n!}{n_1! \cdot n_2! \cdot \cdots \cdot n_k!}
$$

Where $n$ is the total number of items to arrange, and $ n_1, n_2, \ldots, n_k $ are the counts of each distinct item.

Thus, the formula becomes:

$$
\frac{8!}{1! \cdot 1! \cdot 2! \cdot 2! \cdot 2!}
$$

Substituting:

$$
\frac{8!}{1! \cdot 1! \cdot 2! \cdot 2! \cdot 2!} = \frac{40320}{1 \cdot 1 \cdot 2 \cdot 2 \cdot 2} = \frac{40320}{8} = 5040
$$

The answer becomes: 5040.

2.13. How many ways can $n$ people sit around a circular table, if the chairs are not labeled?

If this was a rectangular table, the answer would be $n!$ (the
arrangements). However, a circular table means that rotations are the
same:

The arrangement:

[1,2,3] would be the same as [2,3,1]. Thus, we have to divide out all
duplicate rotations.

For [1,2,3], there are 3 arrangements that are the same:

[1,2,3]
[2,3,1]
[3,1,2]

Thus, we have to divide $n!$ by $n$, which is $(n - 1)!$

2.14. Given $n \geq 3$ points in the plane, such that no three of them belong to the same line, how many lines are determined by these points?

2.15. Given $n \geq 3$ points in space, such that no four of them belong to the same plane, how many planes are determined by these points?

2.16. Given a convex $n$-gon, such that no two lines determined by the vertices of the $n$-gon are parallel, and no three of them intersect at the same point, determine the number of points of intersection of these lines that are
(a) inside the $n$-gon;
(b) outside the $n$-gon.

2.17. A group consists of six mathematicians. How many ways can they form five
committees each consisting of three members, such that no two of
these committees consist of the same three mathematicians?

To get 3 members in a group from 6 where order doesn't matter, we have
to find 6 choose 3:

$$
\binom{6}{3} = \frac{6!}{3!(6-3)!} = \frac{6 \times 5 \times 4}{3 \times 2 \times 1} = 20
$$

Thus, there are twenty unique committees.

Next, select any five of these 20 committees. This is 20 choose 5.

$$
\binom{20}{5} = \frac{20!}{5!(20-5)!} = \frac{20 \times 19 \times 18 \times 17 \times 16}{5 \times 4 \times 3 \times 2 \times 1} = 15,504
$$

This is 15504.

Sure! Here's the restated snippet with line breaks at 80 characters:

2.18. Let us take a deck of cards consisting of 8 red, 8 blue, 8 yellow, and 8
green cards. Cards of the same color are numbered $\{1, 2, \ldots, 8\}$. How many
ways can 6 cards be chosen such that at least one card of each color is chosen?

2.19. Peter has 12 relatives (five men and seven women), and his wife also has
12 relatives (five women and seven men). They do not have common relatives.
They decide to invite 12 guests, six each of their relatives, such that there are
six men and six women among the guests. How many ways can they choose 12
guests?

2.20. Let $k \geq n + 1$. How many ways can $n$ 0’s and $k$ 1’s be arranged
in a sequence, such that no two 1’s are adjacent?

2.21. Twelve books are arranged in a sequence. How many ways can five books
be chosen such that no two of them are adjacent in the sequence?

2.22. Twelve knights are arranged around King Arthur's Round Table. All of
them are quarreling with their neighbors. How many ways can King Arthur
choose five knights such that no two of them are quarreling?

2.23. How many $n$-digit positive integers $c_1c_2 \ldots c_n$ are there, such
that $1 \leq c_1 \leq c_2 \leq \cdots \leq c_n \leq 9$?

2.24. How many 6-digit positive integers are there such that there are exactly
three distinct digits in the decimal representation of each of them, and the digit
0 does not appear?

2.25. How many different words can be obtained by permuting the letters of the
word LOCOMOTIVE, such that no two O’s are adjacent?

2.26. All $k$-arrangements of elements $a_1, a_2, \ldots, a_n$ are written
down. Determine how many times the element $a_1$ is written down.

2.27. A box contains 36 yellow, 27 blue, 18 green, and 9 red balls. Balls of the
same color are indistinguishable. How many ways are there to choose 10 balls
from the box?

2.28. Determine the number of 0’s at the end of the decimal representation of
the positive integer $144!$.

2.29. Prove that the product of $k$ consecutive positive integers is divisible by
$k!$.

2.30. Let $a_1, a_2, \ldots, a_n$ be nonnegative integers. Prove that
$a_1! a_2! \cdots a_n! \leq (a_1 + a_2 + \cdots + a_n)!$.

2.31. Determine the sum of all 4-digit positive integers, such that there are two
different even digits and two equal odd digits in the decimal representation of
each of them.

We split this problem into finding the combinations of numbers and then
their sums.

First, we must choose two different even digits, which is
$\binom{5}{2}$.

Then, since both of the odd digits must be the same, this is: $\binom{5}{1}$.

Finally, the ways this can be arranged:

$$\frac{4!}{2!2!}$$

$$
\text{Total ways} = \binom{5}{2} \times \binom{5}{1} \times \frac{4!}{2!2!}
$$


$$
\text{Total ways} = 10 \times 5 \times 6 = 300
$$

Thus, there are 300 total ways.

Now we need to calculate the sum of all these numbers.

For each fixed combination of \( E_1, E_2, O \):
- Each digit (even or odd) appears in each decimal place (thousands, hundreds, tens, units) equally due to symmetry in arrangement.
- Thus, each chosen even digit \( E_1, E_2 \) appears 3 times in each place (since there are 3 ways to choose 2 out of 4 places for evens).
- Each chosen odd digit \( O \) appears twice in each place (since there are 2 ways to choose 2 out of 4 places for odds).

Therefore, the contribution of each place value for a specific combination of \( E_1, E_2, O \):

If the number structure is \( 4 \times 1000 + 4 \times 100 + 4 \times 10 + 4 \times 1 \) for each set of choices, then:
\[
\text{Contribution of } E_1: (E_1 \times 3000 \text{ each for 3 positions}) \times 10 \times 5 = 150000 \times E_1
\]
\[
\text{Contribution of } E_2: (E_2 \times 3000 \text{ each for 3 positions}) \times 10 \times 5 = 150000 \times E_2
\]
\[
\text{Contribution of } O: (O \times 2000 \text{ each for 2 positions}) \times 10 \times 5 = 100000 \times O
\]

Summing up for all valid combinations:
\[
E_1, E_2 = \{0, 2, 4, 6, 8\} \quad \text{sum of even digits}=20
\]
\[
O = \{1, 3, 5, 7, 9\} \quad \text{sum of odd digits}=25
\]

\[
\sum_{\text{even}} 150000 \times (0 + 2 + 4 + 6 + 8) = 150000 \times 20 = 3000000
\]
\[
\sum_{\text{odd}} 100000 \times (1 + 3 + 5 + 7 + 9) = 100000 \times 25 = 2500000
\]

Combining all:
\[
3000000 + 2500000 = 5500000
\]

So, the sum of all 4-digit positive integers, such that there are two different even digits and two equal odd digits in the decimal representation of each of them, is:

\[
\boxed{5500000}
\]

600.

2.32. All digits $\{0, 1, \ldots, 9\}$ are written down on a sheet of paper. After a
$180^\circ$ rotation, the digits 0, 1, and 8 do not change meaning, the digit 6
becomes 9, and 9 becomes 6. The remaining digits lose their meaning. How many
7-digit positive integers are there, such that they remain the same after the
$180^\circ$ rotation?


2.33. How many 3-combinations $\{x_1, x_2, x_3\}$ of elements $\{1, 2, \ldots, 3n\}$ are
there, such that $x_1 + x_2 + x_3$ is divisible by 3?

2.34. Determine the total number of 0’s in the decimal representations of the
positive integers $\{1, 2, \ldots, 10^9\}$.

2.35. How many positive integers are there in the set $S = \{1, 2, \ldots, 10^7\}$,
such that the digit 1 does not appear in their decimal representations?

2.36. Determine the sum of all digits that appear in the decimal representations of
all positive integers from the set $\{1, 2, \ldots, 1,000,000\}$.

2.37. How many positive integers less than $10^n$ are there, such that no two
adjacent digits in their decimal representations are equal to each other?

2.38. How many $n$-arrangements of the elements 0 and 1 are there, such that no
two adjacent terms in each of them are both equal to 1?

2.39. How many $n$-arrangements of the elements 0, 1, \ldots, $n$ are there with an
even number of 0’s?

2.40. Let us take 6 red balls, 7 blue balls, and 10 yellow balls. Balls of the same
color are numbered and hence distinguishable. How many ways are there to arrange
the balls in a sequence such that any red ball is between a blue and a yellow ball,
and no blue ball is adjacent to a yellow ball?

2.41. According to the rules, a set of a volleyball game is won by the team that first
scores 25 points with a minimum two-point advantage. After each point the result is
written down, for example 0 : 1, 0 : 2, 1 : 2, 2 : 2, \ldots The first integer always
shows points scored by the host team. Suppose that the final result of a set is 25 : n.
How many ways can this result be reached,
(a) if $n \in \{0, 1, 2, \ldots, 23\}$ is a fixed integer?
(b) if we know only that $n \leq 23$?
