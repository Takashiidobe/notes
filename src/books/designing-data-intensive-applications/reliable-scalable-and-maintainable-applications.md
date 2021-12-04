---
title: reliable-scalable-and-maintainable-applications
---

, Scalable and Maintainable Applications"

# Reliable, Scalable, and Maintainable Applications

Next:
[data-models-and-query-languages](data-models-and-query-languages.md)

Data Intensive Applications use the following building blocks:

- Storing Data (Databases)
- Cache Data (Caches)
- Index Data (Search Index)
- Send Messages (Stream Processing)
- Crunch Data (Batch Processing)

## Aspects of software systems

1.  Reliability

- The system should continue to work correctly (even with software,
  hardware and human fault)

2.  Scalability

- As the system grows (in data volume, traffic volume, or complexity)
  there should be reasonable ways of dealing with that growth.

3.  Maintainability

- Over time, many people will be working on the system. They should be
  able to make changes (fixes and features) productively.

### Reliability

Faults: faults occur when one part of the system misbehaves.

Failure: the system as a whole misbehaves.

#### Hardware faults:

- RAM becomes faulty
- The grid blacks/browns out
- The internet stops working
- Hard disks fail

Hard disks have a mean time to failure of 10 to 50 years. Therefore, on
a cluster with 10,000 disks, one disk should die per day.

#### Software Errors:

- A leap year second bug in 2012 which caused applications to hang in
  the linux kernel
- An infinite loop eats up all of a shared resource, starving other
  processes.
- An external service slows down
- Cascading failure

#### Human Errors:

- Make interfaces hard to use wrong.
- Create sandbox environments
- Test thoroughly at all levels
- Allow quick recovery (rolling back)
- Add lots of metrics

### Scalability

Scalability is generally in response to one part of the load increasing.
That could be read or write volume, or read or write throughput.

#### Describing Load

- Posting a tweet:

A User can publish a new message to their followers (4.6k rps, 12krps
@peak)

- Viewing Home Timeline:

A user can view tweets posted by the people they follow (300k rps)

How do we handle both operations?

1.  Posting a tweet simply inserts the new tweet into a global
    collection of tweets. When a user requests their home timeline, look
    up all the people they follow, find all the tweets for each of those
    users, and merge them (sorted by time). In a relational database
    like in Figure 1-2, you could write a query such as:

```sql
SELECT tweets.*, users.* FROM tweets
JOIN users ON tweets.sender_id = users.id
JOIN follows ON follows.followee_id = users.id
WHERE follows.follower_id = current_user
```

2.  Maintain a cache for each user's home timeline---like a mailbox of
    tweets for each recipient user (see Figure 1-3). When a user posts a
    tweet, look up all the people who follow that user, and insert the
    new tweet into each of their home timeline caches. The request to
    read the home timeline is then cheap, because its result has been
    computed ahead of time.

Twitter does the second approach these days. This is because the read
volume is much higher than the write volume, but this has the tradeoff
of increasing write volume (if everyone has on average 75 followers,
4.6k * 75 == 345k writes per second).

Some celebrities might have 1M+ followers. In that case, twitter employs
the first approach, as every time a celebrity would write a tweet, 1M
writes in a few seconds would overload the writers to this service.

### Describing Performance

- When you increase a load parameter and keep the system resources the
  same, how is performance affected?
- When you increase a load parameter, how much do you need to increase
  resources to keep performance unchanged?

Normally we use p90, p95, p99, p999 (90th, 95th, 99th, 99.9th)
percentiles to measure performance.

Amazon for example optimized for the p999 customer's experience,
because they spent a lot on the platform, and were more likely to spend
more. However, the p9999 experience didn't matter as much, so they
stopped optimizing at that point.

SLAs (service level agreements) are a contractual bound where customers
can find out what is the expectation for the service to be up.

### Approaches for Coping with Load

An architecture that is appropriate for one level of load is unlikely to
cope with 10 times that load. For a fast growing service, you'll want
to rethink your architecture every so often to deal with that.

To create systems like this, you may want to go for a shared-nothing
architecture, which increases load horizontally.

Remember that a lot of this is reliant on system load; a system built to
handle 100,000 rps with a payload of 1kB is different from one with 3
rps with a 2GB payload, even though both systems have the same
throughput.

### Maintainability

1.  Operability

- Make it easy for operations teams to keep the system running
  smoothly.

2.  Simplicity

- Make it easy for new engineers to understand the system, by removing
  as much complexity as possible from the system.

3.  Evolvability

- Make it easy for engineers to make changes to the system in the
  future, adapting it for unanticipated use cases as requirements
  change.

#### Operability: Making life easy for Operations

- The operations team should make the following easy:

1.  Monitoring the health of the system
2.  Making the platform easy to debug
3.  Keeping software up to date
4.  Anticipating future capacity problems before they occur
5.  Establishing good practices for deployment and configuration
    management
6.  Maintaining processes of the system
7.  Preserving the organization's knowledge about the system.

#### Simplicity: Managing Complexity

Making a system simpler often means reducing accidental complexity, and
finding good abstractions.

#### Evolvability: Making Change Easy

Following agile, TDD, allowing the system to be more modular through the
use of interface segregation.

Next:
[data-models-and-query-languages](data-models-and-query-languages.md)
