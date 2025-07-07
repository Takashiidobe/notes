---
title: Availability
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Sunday, July 6th 2025, 8:42:24 pm
---

Prev: [latency-and-throughput](latency-and-throughput.md)
Next: [caching](caching.md)
# Availability

- Customers wouldn\'t be happy if a website was down \-- we would lose
  money.

- Some products are life or death, like airplane systems.

- Cloud providers like AWS and GCP also have high availability
  (99.95%)

- We measure availability by how much uptime they have.

- 99% - Two Nines - 3.65 days of downtime

- 99.9% - Three Nines - 8 hours of downtime

- 99.99% - Four Nines - 1 hour of downtime

- 99.999% - Five Nines - 5 minutes of downtime (High Availability)

- Service Level Agreement (SLA) are a guarantee of how much uptime is
  required.

- Service Level Objective (SLO) are similar.

- How do we increase availability?

- eliminate single points of failure.

- Make sure there's redundancy.

  - If you have one server, have multiple.
  - If you have multiple servers, get more load balancers.

- Active redundancy is like leader election, when a node crash
  reconfigures itself.

Prev: [latency-and-throughput](latency-and-throughput.md)
Next: [caching](caching.md)
