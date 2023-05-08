# Design a Messaging Service

## Requirements

1. 1:1 conversations between users
2. The service should keep persistent storage of chat history.

- This can be on their local device (in the form of caches), but we also
  need to keep a copy, since caches can be wiped at any time without our
  knowledge (clearing cookies/mobile data)

## Performance Requirements

1. Must be real time, so be fast.
2. System should be consistent -- users should never see the wrong
   message/messages that haven't been sent.
3. System should be available, but prefer consistency over availability
   always, since showing the wrong message can cause disasters.
4. System must be linearizable. If operations are not ordered properly,
   there can also be lots of damage done (e.g. blocking someone then
   trash talking them causes problems if the operations are reordered.)

## Capacity estimation

500 million daily active users. Each user sends 40 messages daily.

20B messages per day.

A message is 100 bytes. So per day, we need 2TB of storage.

For about 5 years of chat history, we'd need 3.5 PB of storage.

This costs us about 25MB of incoming data per second upstream and
downstream (2TB / 86400)

(We can always compress and decompress data. Given textual data, assume
a 2-4x compression rate, so we can support 6MB-25MB up and downstream).

Can we archive some of this data/hold it in non-hot storage?

What is the cost of this?

1GB/Month costs about 1 cent for Disk.
1GB/Month costs about 10 cents for SSD.
1GB/Month costs about $1 for RAM storage.

About 5M a month to store all in RAM.

## Data Schema

- User table (`user_id`)
- Messages (`message_id`, `from_id`, `to_id`, message) (index on
  `from_id`, `to_id`), but how do we make updates fast
  (use pagination, not offsets here).

How do we guarantee linearizability and stronger consistency? What
should we do when certain nodes aren't reachable?

Use pagination. For range queries. Limit/Offset related stuff doesn't
work.

## Message Handling

1. Pull/Push. Should the user poll the server, and ask for new messages
   periodically, or should they keep a bidirectional socket open with
   the server for new messages?

- Pull is old school (not all devices support bidirectional sockets, a
  la HTTP 1.2), so we may have to support this for very old devices.

- Once per second = 500M queries per second to web services.

- Push is more efficient, since the overhead of opening a connection in
  HTTP can be amoritized over the cost of a session. As well, Server
  Side Events are very useful for this.

- Most smartphones.

## Maintaining Consistency

- Timestamps won't work because this is a distributed system.
- We want the server that processes messages to increment a number to
  preserve ordering for the same client.

## Storing and retrieving messages from the database

- We should prefer to use a NoSQL solution, since our write throughput
  is pretty high (20B messages per day or about 250k messages per
  second). Some sort of wide columnar store might be nice, like HBase or
  RocksDB.

## Data Partitioning

- How should we partition data? The User schema should be global, but
  the messages should be partitioned by `user_id`, so we can fetch all
  messages for a user.
