---
title: design-a-voting-system
---

A Voting System

# Design a Voting System

Design a voting system. 100M users will be logging in within a window of
24h (not necessarily uniformly). Every user will be able to choose from
a fixed list of options. If the user has already voted the system should
not let them to vote a second time. Additional constraint: only the
first 100K votes are accepted. If the quota is exceeded any attempt to
vote should be rejected.

## Authentication

- First of all, we need to find a way to authenticate our users,
  possibly in advance with an automated system connected to ID (social
  security, passport) to prevent fraud.

## Voting

Since we can only allow 100k votes, and it would be a bad (but not
terrible UX) to invalidate anyone who makes a vote after the 100k one.
We can try to make this work by having a leader follower setup, with the
leader writing ahead to the followers, and if a leader falls, having a
new leader election.
