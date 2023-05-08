# Design a Distributed Rate Limiter

We want to design a rate limiter.

## Algorithms

Token Bucket:

A bucket that maintains a rolling, and accumulating budget of usage as
tokens. A token bucket adds tokens at some rate. When a request arrives, it withdraws a token. If there are no tokens in the bucket, the service tries to shed load.

Leaky Bucket:

A bucket that
