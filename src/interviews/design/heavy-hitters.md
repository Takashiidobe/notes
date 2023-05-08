# Heavy Hitters

We have a service in production that is receiving a lot of traffic. We
get a few spikes in traffic from a few users that is Dosing our service
(causing severe degradation). How would we deal with this?

1. Map of { people -> queries} is big O(n).

We want to find the mode of this sequence, which takes O(n) time and
O(n) space.

(Let's say this is too expensive).

We can find the elements that occur at least n% of the time in O(1/n)
memory.

## Implementation

- Have a current winner and a counter.
- Process elements one by one.
- When processing e,
  - if e is already the winner, then increment the counter.
  - else if the counter is zero, set the current winner to e and counter
    to 1.
  - otherwise, decrement the counter.
- At the end, check if the current winner is indeed a majority element
  -- iterate through the array a second time to count exactly how
  often the winner occurs.

This can be generalized for any percentage from 0-100. (X = 1 / k)

We can do this by having k - 1 current winners + counters.
