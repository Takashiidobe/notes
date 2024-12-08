---
title: Types of PoS
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Saturday, December 7th 2024, 6:44:19 pm
---

[Proof of Work](./proof-of-work.md) has a few problems:

1. Energy expenditure (unscalable)
2. Transactions per second is low (unscalable)
3. Eventually power gets held by those who own specialized hardware
   (centralized)

In Proof of Stake, no electricity is spent solving cryptographic
puzzles. Instead, holders of the currency can "stake" their tokens,
which nets them some benefits.

When the tokens are staked, they are put into a pool of all currently
staked tokens, which then decide on the order of transactions in the
blockchain.

# Types of PoS

## Delegated

In Delegated PoS (DPoS), a fixed number of elected nodes are responsible
for creating blocks in a round-robin order. These are voted for by token
holders.
This is kind of like how democracy works. This fixes the scalability
issue of a blockchain, but sacrifices decentralization.

## Bonded

In Bonded PoS (BPoS) there are no elected nodes, but voting power is
proportional to the stake. Thus, wealthy participants are better off.

## Pure

In Pure PoS (PPoS) there are no elected nodes. Instead, a random set of
participants are chosen from the staking pool and given a cryptographic
puzzle that when solved, validates a transaction on the blockchain.
As long as 2/3 of the participants were honest, this change is committed
to the blockchain. This makes it so the system is scalable, secure, and
decentralized.
