---
title: "Bitcoin"
pdf_url: "[[bitcoin.pdf]]"
---

## Notes

Bitcoin is a p2p electronic cash system that allows two parties to send payments over the internet without a financial intermediary. This is done by using a decentralized network.

- Each coin is a chain of digital signatures by using their private key. 
- To prevent double spending, all transactions are publicly broadcast, and grouped into blocks. 
- A distributed timestamp server orders the blocks, so everyone agrees on which transactions came first.

The network uses Proof of Work, where nodes hash a block header with a nonce until the hash has a required number of leading zero bits.
Blocks reference the previous block's hash, forming an immutable chain of blocks.
The longest chain is the canonical history -- others are branches, which are normally disregarded. However, it's possible to get 51% of compute on the chain to fabricate your own history and have nodes agree that history is legitimate.

The protocol:

- Nodes broadcast new transactions
- Each node collects transactions into a block
- Nodes perform PoW to find a block hash
- The first node to find a valid block broadcasts it.
- Other nodes verify it, and if valid, accept it and add it to their current chain.

To incentivize participation:

- The first transaction in each block creates new coins as a reward for the miner.
- Transaction fees are paid to the miner. 
- A rational miner is thus better off following the rules.

Transactions are arranged in a merkle tree, allowing old transactions to be pruned.
Privacy is achieved because users can use public keys and addresses which change for each transaction. Thus, even though all transactions are public, as long as the public key is anonymous, it's uncertain who is making the transaction.




