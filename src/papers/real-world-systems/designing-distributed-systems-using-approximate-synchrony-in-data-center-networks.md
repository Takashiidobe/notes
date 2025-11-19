---
title: "Designing Distributed Systems Using Approximate Synchrony In Data Center Networks"
pdf_url: "[[designing-distributed-systems-using-approximate-synchrony-in-data-center-networks.pdf]]"
---
This paper implements two protocols, one called Mostly-Ordered Multicast (MOM), and one called Speculative Paxos, that uses the properties of a datacenter (fast packets, reliably ordered, nearly identically to consumers) to speed up network transmissions.

## Multicast in the DC

Normal multicast can reorder messages because of network hops + congestions -- consumers can see packets in a different order from their neighbors.

There are three network-level designs discussed in the paper, each with more constraints and less performance.

1. **Toplogy-aware multicast**
	- Route multicast traffic so all receives see the same number of hops
	- This prevents reordering due to path length differences.
2. **High-priority multicast (QoS)**.
	- Topology aware multicast sends MOM packets in a priority queue over other traffic.
	- Less reordering due to queueing and congestion. Skew is reduced.
3. **In-network serialization**
	- Route all multicasts for a group through a switch which handles serialization.
	- As long as the switch preserves per-port FIFO, this has perfect ordering.

They note that reorder rates of packets with topology aware multicast goes from ~10% to 0.1%. 

## Speculative Paxos

Given this design of multicast, the authors introduce speculative paxos, a state machine replication protocol.

- Using multicast from clients to all replicas
- letting replicas speculatively execute operations in order by MOM
- Ensures correctness up to $f$ failures.

This is done with:

- Speculative execution + hashing:
	- Each replica gets a sequence number and executes operations as they arrive, logging them as **SPECULATIVE**.
	- It maintains a rolling summary hash over the log, for fast prefix checking.
- Clients wait for speculative replies from a quorum, $f$ + $\frac{f}{2}$ + 1 replicas. 
	- If there's a quorum, the client commits after two message delays.
- Period synchronization
	- A leader runs a lightweight sync to confirm replicas agree on prefixes
	- Matching quorums mark operations up to that one as committed and inform replicas
- Reconciliation
	- If hash mismatches or timeouts reveal divergence, the system runs a reconciliation protocol
	- And the leader merges logs, where operations eventually appear in some order.
	- Replicas then rollback speculative operations that don't match the combined log and re-execute.
## Results 

On a 12-switch testbed:

- **40%** lower latency, and **2.6x** higher throughput compared to paxos.
- However, when reordering is >0.1%, reconciliation costs grow, and performance dips below paxos'.