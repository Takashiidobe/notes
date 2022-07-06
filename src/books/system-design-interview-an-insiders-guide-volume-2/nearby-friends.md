---
title: "Nearby Friends"
---

# Nearby Friends

Prev: [proximity-service](proximity-service.md)
Next: [google-maps](google-maps.md)

This chapter focuses on a feature for finding nearby friends.

## Questions and Answers

Q: how close is nearby?
A: 5 miles. This should be configurable.

Q: is this the straight-line distance between two users, ignoring
landmarks?
A: that's fine

Q: how many users? Is 100M DAU ok?
A: yes

Q: do we need to store location history?
A: yes, location history is valuable for machine learning.

Q: should we allow inactive (friends that haven't moved for 10 minutes),
or should we display the last known location?
A: inactive friends shouldn't be shown.

Q: what about Data privacy laws like GDPR or CCPA?
A: let's not worry about it.

## Functional requirements

- Users should be able to see nearby friends, with a distance and
    timestamp showing when it was updated.
- Updates should propagate every few seconds.

## Non-functional requirements

- Low latency (should be fast)
- Reliability (occasional data loss is ok)
- Eventual consistency (a few seconds delay in location data loss is
    ok)

## Back of the Envelope Estimation

- Nearby friends are within a 5-mile radius
- Location refresh in 30 seconds. Walking speed is about 2-4 mph, so
  location doesn't change meaningfully in 30 seconds.
- 100M DAU
- Assume 10M concurrent users
- On average, a user has 400 friends. Assume all of them use the nearby
  friends feature.
- The app displays 20 nearby friends per page and can load more nearby friends upon request.
- Assume there

- QPS: 10 million concurrent users / 30 = 333k qps

## High Level Design

- This design could be done purely peer-to-peer, but would be difficult
  (we don't know how powerful the client's devices are, and it might
  be difficult to poll all friends for location updates).

- Instead, we will have the user push updates to a backend, which will
  then push updates to all friends. This requires about 14 million
  updates per second, which makes this non-trivial.

## Proposed Design

Client -> LB -> Websockets Server -> Redis -> Location Cache -> Location DB
             -> API Server -> User Database

We use websockets to connect clients to the server, since they are less
expensive than HTTP connections.

Redis caches locations of friends, with a TTL set on each entry in the
cache. When the TTL expires, requests must go back to the database.

The Location history database stores the data for use in a data cub or
similar in the future.

We use Redis pub/sub (like kafka) to build topics that users can
subscribe to for updates. All users publish location information to
their respective topic, and then subscribers can take updates from all
the friends they are interested in, if they are within a nearby radius.

## Data Model

### Location Cache

| Key     | Value                            | Other    |
|---------|----------------------------------|----------|
| user_id | {latitude, longitude, timestamp} | TTL 60 s |

This location cache only needs to hold a (u64, f64, f64, u64) value for
each user, which costs 32 bytes per user. For a billion users, this
would only cost 32 GB, which is easy to store on a single node in
memory.

### Location History Database

This database would look like the cache, except it would persist more
than one entry. It might be good to use a write-heavy db like Cassandra
for this.

## Design Deep Dive

### Websocket servers

Care must be taken to drain existing connections before swapping out
websocket servers -- kubernetes handles this by creating new nodes and
letting them drain before removing them from the cluster.

### Redis pub/sub

Redis pub sub would require about 200 GB to hold all channels (20 bytes
of pointers for each subscriber, with 1e8 * 20 * 1e2 / 1e9 = 2e10 bytes).
We could hold this in a server with 256 GB of memory pretty easily, or
replicate it for redundancy.

We should take care to persist the data, since updates are required to
be stateful, but redis' raft implementation leaves much to be desired.
I'd prefer distributed kafka here.

Prev: [proximity-service](proximity-service.md)
Next: [google-maps](google-maps.md)
