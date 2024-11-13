---
title: Problems
date created: Thursday, June 20th 2024, 9:11:49 pm
date modified: Tuesday, November 12th 2024, 8:30:15 pm
---
# Problems

## 1. To Begin or Not to Begin?

An urn contains `k` black balls and a single red ball. Peter and Paula draw
without replacement balls from this urn, alternating after each draw until the
red ball is drawn. The game is won by the player who happens to draw the
single red ball. Peter is a gentleman and offers Paula the choice of whether
she wants to start or not. Paula has a hunch that she might be better off if
she starts; after all, she might succeed in the first draw. On the other hand,
if her first draw yields a black ball, then Peter’s chances to draw the red ball
in his first draw are increased, because then one black ball is already removed
from the urn. How should Paula decide in order to maximize her probability
of winning?

Let's solve this by looking at values of `k`.
If `k` is 0, Going first has a 100% chance of winning, and second has a
0% chance.
If `k` is 1, Going first has a 50% chance of winning, and second has a
50% chance of winning.
If `k` is 2, Going first means you can take 2/3 of the balls vs 1/3 if
you go second, so going first is better.
If `k` is 3, Going first or second means you take 2/4 balls, so this is
also 50/50.

Thus, even and odd numbers of `k` are the only difference, where if `k`
is odd, then you have a 50/50 chance of winning as either first or
second, and if `k` is even, you have an edge, so you should always go
first.

## 2. A Tournament Problem

Ten players participate in the first round of a tennis tournament: 2 females
and 8 males. Five single matches are fixed at random by successively drawing,
without replacement, the names of all 10 players from an urn: the player drawn
first plays against the one whose name comes up second, the third against the
fourth, etc.
a. What is the probability that there will not be a single match involving
two female players? Is this probability smaller, equal to, or larger than the
corresponding probability with 20 females and 80 males?
b. Try to answer the general case in which there are 2n players, of whom
2 ≤ k ≤ n are female. What is the probability p(k, n) that among the n
matches there will not be a single one involving two female players

- For the chance that there will not be a single match involving two
  female players, we can calculate the total combinations of pairs
  (10c2), or 45, and the amount of pairs where there is a woman vs a
  woman (5, since the pair can be in any of the 5 games).
- Thus the chance is 40/45 or 8/9 for there to be no woman vs woman
  game.
- For the case with 20 females and 80 males, it drops to about 9%.

## 3. Mean Waiting Time for 1 − 1 vs. 1 − 2

Peter and Paula play a simple game of dice, as follows. Peter keeps throw-
ing the (unbiased) die until he obtains the sequence 1 − 1 in two successive
throws. For Paula, the rules are similar, but she throws the die until she
obtains the sequence 1 − 2 in two successive throws.
a. On average, will both have to throw the die the same number of times?
If not, whose expected waiting time is shorter (no explicit calculations are
required)?
b. Derive the actual expected waiting times for Peter and Paula

a. The mean waiting time for Peter is longer than for Paula, because
Peter has to roll 1-1, and if he rolls anything other than a 1 on a
roll, he has to restart. For Paula, if she rolls anything other than a 1
into a 1, she can continue on that way.

We can model this using a game tree for Paul:

- With a probability `p` ($\frac{1}{6}$), Paul will roll a 1.
    - With a probability `p` ($\frac{1}{6}$) Paul will again roll a 1.
    - With a probability `1 - p` ($\frac{1}{6}$), Paul won't roll a 1 and restart.
- With a probability `1 - p`, ($\frac{5}{6}$), Paul won't roll a 1 and restart.

Thus, there are three outcomes:

The outcome that ends the game, 1-1 has a chance of $p^2$ or ($\frac{1}{36}$.
The outcome that he rolls a 1 and then anything else is $p * (1 - p)$ or
$\frac{5}{36}$.
The outcome that restarts is $1 - p$ or $\frac{5}{6}$.

The first two outcomes take 2 rounds and the last one takes 1 round.
Thus, the total waiting time is the time taken * the probability they
occur:

$$ W = (1 + W) * (1 - p) + (2 + W) * p(1 - p) + 2p^2 $$

Simplifying:

$$ W = \frac{1 + p}{p^2} $$

When $p = \frac{1}{6}$, W = 42.

For Paula's case, we can model this as a markov chain:

There are three states, the starting state $S_0$, a state for when the
last throw was a 1 $S_1$, and the final state of 1-2, $S_2$.

$$
\begin{pmatrix}
\frac{5}{6} & \frac{1}{6} & - \\
\frac{2}{3} & \frac{1}{6} & \frac{1}{6} \\
- & - & 1
\end{pmatrix}
$$

Thus, we can find the expected waiting time for both $S_0$ and $S_1$ as
follows:

$$
W_0 = 1 + \frac{5}{6} W_0 + \frac{1}{6} W_1
$$

$$
W_1 = 1 + \frac{2}{3} W_0 + \frac{1}{6} W_1 + \frac{1}{6} W_2
$$

This gives us W = 36, solving for $W_0$.

## 4. How to Divide up Gains in Interrupted Games
Peter and Paula play a game of chance that consists of several rounds.
Each individual round is won, with equal probabilities of $\frac{1}{2}, by either Peter or
Paula; the winner then receives one point. Successive rounds are independent.
Each has staked $50 for a total of $100, and they agree that the game ends as
soon as one of them has won a total of 5 points; this player then receives the
$100. After they have completed four rounds, of which Peter has won three
and Paula only one, a fire breaks out so that they cannot continue their game.
a. How should the $100 be divided between Peter and Paula?
b. How should the $100 be divided in the general case, when Peter needs
to win a more rounds and Paula needs to win b more rounds?

a. In the case where Peter has 3 wins and Paula has 1, Peter needs to
win 2 times in the next 5 rounds, whereas Paula needs to win 4 times in
the 5 rounds.

We can enumerate all the cases, or we can just play 5 rounds and count
the times where Peter wins 0 or 1 times out of the 5, to find out
Paula's winning chance:

$$ \binom{5}{0} \left( \frac{1}{2} \right)^5 + \binom{5}{1} \left( \frac{1}{2} \right)^5 = \frac{6}{32} $$

This is $\frac{3}{16}$, or Peter should receive $\frac{13}{16}$ of the
portion, and Paula should receive $\frac{3}{16}$.

b. In the general case, we can apply the same technique:

The number of rounds that can be played is $a + b - 1$.

We can apply the same formula in the general case, where we count $[1, a)$
and multiply it by $\frac{1}{2}^{a + b - 1}$.

## 5. How Often Do Head and Tail Occur Equally Often?
According to many people’s intuition, when two events, such as head and
tail in coin tossing, are equally likely then the probability that these events
will occur equally often increases with the number of trials. This expectation
reflects the intuitive notion that in the long run, asymmetries of the frequencies of head and tail will “balance out” and cancel.
To find the basis of this intuition, consider that $2n$ fair and independent
coins are thrown at a time.
a. What is the probability of an even $n : n$ split for head and tail when
$2n = 20$?
b. Consider the same question for $2n = 200$ and $2n = 2000$.

a. To count the even n : n split, we can count the number of possible
outcomes and subtract out the non n : n splits to get the chance of an
n : n split.

In the case of 20 coin flips, there are $2^20$ or about 1 million ways
to flip them in a way where order doesn't matter.

To count the number of times where there are exactly 10 heads and 10
tails:

$$\binom{20}{10} = \frac{10! \cdot 10!}{20!}$$

Or about 184,756. Dividing this by $2^20$, we get 17.62%.

b. This approaches the normal distribution as $n$ increases.

We can approximate this probability as the following, trying to create a
rectangle of the area below the curve:

$$\frac{1}{\sqrt{n\pi}}$$

## 6. Sample Size vs. Signal Strength
An urn contains six balls — three red and three blue. One of these balls
— let us call it ball A — is selected at random and permanently removed
from the urn without the color of this ball being shown to an observer. This
observer may now draw successively — at random and with replacement —
a number of individual balls (one at a time) from among the five remaining
balls, so as to form a noisy impression about the ratio of red vs. blue balls
that remained in the urn after A was removed.
Peter may draw a ball six times, and each time the ball he draws turns
out to be red. Paula may draw a ball 600 times; 303 times she draws a red
ball, and 297 times a blue ball. Clearly, both will tend to predict that ball A
was probably blue. Which of them — if either — has the stronger empirical
evidence for his/her prediction?

They both have the same amount of empirical evidence.
The only thing that matters is the difference between the red and blue
balls being drawn, which is 6 for both.

To calculate the probability that the ball drawn was blue for Peter, we
can use Bayes theorem, calculating the probability that the ball drawn
was blue or red:

$$P(A = b \mid \langle rrrrrr \rangle) = \frac{1}
{1 + \left( \frac{2}{3} \right)^6} = 0.919$$

For Paula, we get the same result:

If we pull blue:
$$P(303r \land 297b \mid A = b) = \binom{600}{303} \left( \frac{3}{5} \right)^{303} \left( \frac{2}{5} \right)^{297}$$

If we pull red:
$$P(303r \land 297b \mid A = r) = \binom{600}{303} \left( \frac{2}{5} \right)^{303} \left( \frac{3}{5} \right)^{297}$$

The chance of blue out of both blue and red:
$$P(A = b \mid 303r \land 297b) = \frac{1}{1 + \left( \frac{2}{3} \right)^6}$$

Which is the same as above.

## 7. Birthday Holidays

The following problem is described in Cacoullos (1989, pp. 35–36).
A worker’s legal code specifies as a holiday any day during which at least
one worker in a certain factory has a birthday. All other days are working
days. How many workers (n) must the factory employ so that the expected
number of working man-days is maximized during the year?

Each worker can work up to 365 days a year. However, if they have the
same birthday, everyones workdays go down by 1. Thus, we want to find
the point at which
