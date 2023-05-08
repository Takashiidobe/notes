# Queueing Disciplines

- `pfifo_fast` is the default, a FIFO queue. This has three bands (queues), where type of service packets are placed in queue 0 (the lowest level), and unless queue 0 is empty, packets from queue 1 won't be sent, and the same for queue 2.
- `token bucket filter` passes packets arriving at a rate that does not exceed some set rate, but allows bursts in excess of this rate (leaky bucket).
- `stochastic fairness queueing` SFQ is a algorithm that uses randomness (hashing) to set a "fair" throughput for each session that sends packets. Each packet is hashed and added ot a queue, and each queue is processed in round robin fashion.
- `Random Early Drop` to avoid congestion, RED pre-emptively drops packets before the buffer becomes completely full. It uses some heuristics based on packet size to figure out which packets to drop.
