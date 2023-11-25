---
title: "Probability and counting"
---

# Probability and counting

Next: [conditional-probability](conditional-probability.md)

## Exercises

### Counting

1. How many ways are there to permute the letters in the word MISSISSIPPI?

There are 11 P 4 ways to choose S, 7 P 4 ways to choose I, 3 P 2 ways to choose P, and one position for M.

Thus, it is the product of the above.

2. (a) How many 7-digit phone numbers are possible, assuming that the first digit can’t
be a 0 or a 1?

There are 8 choices for the first digit and 10 choices for the rest of the 6. $8 * 10^6$.

(b) Re-solve (a), except now assume also that the phone number is not allowed to start
with 911 (since this is reserved for emergency use, and it would not be desirable for the
system to wait to see whether more digits were going to be dialed after someone has
dialed 911).

We can take the previous answer, $8 * 10^6$ and subtract it with how many phone numbers could start with 911, which would be $10^4$, so $(8 * 10^6) - 10^4$.

3. Fred is planning to go out to dinner each night of a certain week, Monday through
Friday, with each dinner being at one of his ten favorite restaurants.
(a) How many possibilities are there for Fred’s schedule of dinners for that Monday
through Friday, if Fred is not willing to eat at the same restaurant more than once?
(b) How many possibilities are there for Fred’s schedule of dinners for that Monday
through Friday, if Fred is willing to eat at the same restaurant more than once, but is
not willing to eat at the same place twice in a row (or more)?
4. A round-robin tournament is being held with n tennis players; this means that every
player will play against every other player exactly once.
(a) How many possible outcomes are there for the tournament (the outcome lists out
who won and who lost for each game)?
(b) How many games are played in total?
5. A knock-out tournament is being held with 2n tennis players. This means that for each
round, the winners move on to the next round and the losers are eliminated, until only
one person remains. For example, if initially there are 24 = 16 players, then there are
8 games in the first round, then the 8 winners move on to round 2, then the 4 winners
move on to round 3, then the 2 winners move on to round 4, the winner of which is
declared the winner of the tournament. (There are various systems for determining who
plays whom within a round, but these do not matter for this problem.)
(a) How many rounds are there?
(b) Count how many games in total are played, by adding up the numbers of games
played in each round.
(c) Count how many games in total are played, this time by directly thinking about it
without doing almost any calculation.
Hint: How many players need to be eliminated?
6. There are 20 people at a chess club on a certain day. They each find opponents and
start playing. How many possibilities are there for how they are matched up, assuming
that in each game it does matter who has the white pieces (in a chess game, one player
has the white pieces and the other player has the black pieces)?

Next: [conditional-probability](conditional-probability.md)
