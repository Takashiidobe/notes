---
title: Caching
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Sunday, July 6th 2025, 8:42:22 pm
---

# Caching

- Caching avoids redoing the same computationally expensive work.

- You can cache requests from the client and the server.

- You can cache requests from the server and the database.

- write-through cache

  - When you write to the database, you write to the cache and the
    database.

- write-back cache

  - When you write to the database, you only update the cache, and
    not the database.
  - Eventually, you write to the database to update.

- caches can become stale if they\'re not updated frequently.

- But caches are expensive\... What are the most important parts of
  the system?

- When is caching good?

  - Immutable data
  - Infrequent Writes
  - When you don\'t care about stale data
  - Strong Invalidation guarantees.

- Eviction Policies:

  - LRU (Least Recently Used)
  - LFU (Least Frequently Used)
  - LIFO (Last In First Out)
  - FIFO (First in First Out)

Prev: \[availability](availability.md) Next:
\[proxies](proxies.md)
