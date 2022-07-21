---
title: "Distributed Message Queue"
---

# Distributed Message Queue

Prev: [google-maps](google-maps.md)
Next: [metrics-monitoring-and-alerting-system](metrics-monitoring-and-alerting-system.md)

## Step 1:

Q: what is the format and size of messages?
A: text, KBs.

Q: can messages be repeatedly consumed?
A: yes.

Q: are messages consumed in the same order they were produced?
A: yes, messages should be consumed in the same order they were
produced.

Q: does data need to be persisted? If so, how long?
A: yes, assume data retention is two weeks.

Q: how many producers and consumers are we going to support?
A: the more the better.

Q: what data delivery semantics should be supported?
A: at-most-once, at-least-once, exactly once.

Q: what's the target throughput and end-to-end latency?
A: high throughput for use cases like log aggregation.

### Non-functional requirements

- High throughput or low latency, configurable based on use cases.
- Scalable.
- Persistent and durable. Data should be persisted on disk, and
  replicated across multiple nodes.

## Step 2: Propose High-Level Design and Get Buy-In

```
 _____________           _________________              ______________
|             | Messages | Message Queue | -----------> | Consumer 1 |
|  Producer   | -------->| | | | | | | | |              |------------|
|_____________|          |_______________| -----------> |-------------|
                                                        |  Consumer 2 |
                                                        |-------------|
```

1. Producer sends messages to a message queue.
2. Consumer subscribes to a queue and consumes the subscribed messages.
3. Message queue is a service in the middle that decouples the producers
   from the consumers, allowing them to operate and scale independently.
4. Both producer and consumer are clients in the client/server model,
   and the message queue is the server.

### Messaging Models

#### Point-to-Point

In a traditional Point-to-Point message queue, a message is sent to a
queue and consumed by only one consumer.

Once the consumer acknowledges a message has been consumed, it is
removed from the queue.

#### Publish-subscribe

In a pub-sub model, a message is sent to a topic, and received by the
consumers subscribing to the topic. Thus, one message can be consumed by
multiple subscribers.

### Topics, partitions, and brokers

Topics persist messages. But if a topic is too large for a single server
to handle, it has to be broken into partitions (shards). Servers that
handle partitions are called brokers.

Each topic partition operates in the form of a FIFO queue. Thus,
messages in a partition are ordered.

Messages sent to topics are actually sent to a partition, with an
optional message key, which would route it to a particular partition.

### Consumer group

To increase read throughput, we require reading data in parallel. To do
so, we can group consumers into groups, and add a constraint that a
single partition can only be consumed by one consumer in the same group.

This allows for scalability by increasing the partition count.

### High-Level Architecture

Thus, the high-level architecture looks like this:
```
        Metadata storage Zookeeper
               v          v
Producers -> Brokers -> Consumers
```

## Step 3: Design Deep Dive

Since this design is both write-heavy and read-heavy, a database is not
a good fit. To fix this, we recommend a Write-ahead log (WAL)

Writes go to an active segment, and when that segment exceeds a certain
size, it is labeled as inactive, and another segment is created.
If all consumers have caught up, segments can be deleted from memory,
freeing memory.

### Schema

| Field Name | Data Type |
|------------|-----------|
| key        | [u8]      |
| value      | [u8]      |
| topic      | &str      |
| partition  | usize     |
| offset     | usize     |
| timestamp  | u64       |
| size       | usize     |
| crc[5]     | [u32]     |

### Batching

- Batching is important to this design, because it allows faster writes
  and reads, avoiding network traffic and the file lock on the segment
  file.

### Producer Flow

Producers who want to send messages have to decide which broker to
connect to. To make this simpler, we can introduce a routing layer which
reads the replica's distribution plan, and routes the message to the
correct location.

### Consumer Flow

The consumer specifies its offset in a partition and receives back a
chunk of events beginning from that position.

#### Push vs Pull

Push: the broker can push messages to the consumer.
Pull: the consumers pull messages from the broker.

Both have some pros, but the pull model allows more consumers to scale,
and is more amenable to batch processing.

### Consumer rebalancing

When a consumer joins, leaves, crashes, or a partition is adjusted, the
coordinator must rebalance consumer groups so only one consumer is
subscribed to a partition.

### State storage

- State storage stores the mapping between partitions and consumers.
- The last consumed offsets of consumer groups per partition.

### Replication

To handle faults in a distributed system, replication is required. In
each broker, a partition is assigned the leader, where producers send
messages to and followers pull from the leader.

#### Acknowledging Writes

A message broker should allow some configuration of write replication:

- `ACK=all` means all replicas have acknowledged the message.
- `ACK=1` means only the leader needs to acknowledge the message.
- `ACK=0` means the producer just sends the message.

## Data delivery semantics

### At-most once

- The producer sends a message asynchronously to a topic without waiting
    for acknowledgement. If the send fails, there is no retry.
- The consumer fetches the message and commits the offset before the
    data is processed. If the consumer fails, there is no retry.

### At-least once

- The producer sends a message with a response callback, setting `ACK=1`
  or `ACK=all`. If the delivery fails, the producer retries.
- The consumer fetches the message and commits only after it has been
  processed properly.
- Messages might be delivered more than once -- this is the best scheme
  if you have idempotent requests.

### Exactly once

- Is this even possible?

## Advanced Features

### Message filtering

Consumers may want to filter messages, which can be implemented in the
metadata service by adding tags to messages, which the broker can index
messages on.

### Delayed messages & Scheduled messages

Some messages might be published, but should only be read after a
certain amount of time has passed. To implement this, the brokers could
have some temporary storage, and a job which moves them to the message
queue when the time has elapsed.

Prev: [google-maps](google-maps.md)
Next: [metrics-monitoring-and-alerting-system](metrics-monitoring-and-alerting-system.md)
