---
title: "Monitoring in a Reliability Engineering World"
---

# Monitoring in a Reliability Engineering World

Prev: [mysql-architecture](mysql-architecture.md)
Next: [performance-schema](performance-schema.md)

SRE's, popularized by Google, now lets teams think about operational
work in a different light:

1. Are we providing an acceptable customer experience?
2. Should we focus on reliability and resilience work?
3. How do we balance new features against toil?

SRE metrics include the following:

1. Service Level Indicators (SLI): How do I measure whether my customers
   are happy?
2. Service Level Objective (SLO): What is the minimum I can allow my SLI
   to be to ensure that my customers are happy?
3. Service Level Agreement (SLA): What SLO am I willing ot agree to that
   has consequences?

After this, we can select an SLI/SLO/SLA to meet our customers with, and
monitor those.

## Monitoring Availability

Talking about availability for an online store, what features are
nonnegotiable and what are nice to have:

What features being down are catastrophic?

What is the shortest possible mean time to recovery (MTTR) we can
promise?

## Monitoring Errors

Lock wait timeouts can be a sign of escalating row-lock contention, and
can signal downtime later on:

Aborted connections can be an indicator of lots of client-side retries,
which consumes resources.

## Proactive monitoring

Steady state monitoring (monitoring for differences from the normal
state) lets us know if something unexpected is happening to the system.

### Disk growth

- Taking up too much space on disk can lead to disk space errors and
  degraded performance. Try to monitor the growth of disk space on
  instances.

### Connection growth

- MySQL can handle a finite pool of connections, which is set by
  configuring `max_connections`. If this grows above 100, you can use
  `pt-kill` to kill stray connections.

### Replication Lag

If an application is replicating too slowly, it can point to too many
writes being handled by the system, and necessitate an architectural
improvement.

### I/O Utilization

If you find that I/O utilization is high, or close to 100%, it can
indicate inefficient queries, like full table scans or not hitting
enough indexes.

### Auto-increment space

Primary Keys in MySQL are signed integers, and can quickly run out of
space. Be careful about this, maybe using BigInt types?

### Backup creation/restore time

Make sure to utilize backups for recovery purposes, and maybe consider
only backing up business critical parts of your database.

Percentiles are your friend: Don't use average, use medians for SLIs!

Prev: [mysql-architecture](mysql-architecture.md)
Next: [performance-schema](performance-schema.md)
