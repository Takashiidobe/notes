---
title: "Causal Consistency (COPS)"
---

# Causal Consistency (COPS)

6.824 2022 Lecture 17: Causal Consistency, COPS

Lloyd et al, Don't Settle for Eventual: Scalable Causal Consistency
for Wide-Area Storage with COPS, SOSP 2011.

the setting: geo-replication for big web sites
  [ 3 datacenters, users, web servers, sharded storage servers ]
  multiple datacenters, to be close to users
  each datacenter has a complete copy of all data
  reads are fast -- from local replica
  can writes be fast also?
 
we've seen two solutions for geo-replication
  Spanner
    reads are local and fast
    write commit waits for replies from other datacenters
    transactions for read and write
  Facebook / Memcache
    reads are local and fast
    all writes go through primary datacenter
    transactions only for updates
  problems:
    writes must wait for wide-area communication
    slow inter-datacenter network makes writes even slower
    failed datacenter can block writes at other datacenters

can we have writes that never have to wait for other datacenters?
  would help fault tolerance, performance, robustness vs slow WAN
  then we'd have fast local reads *and* writes
  puzzle: what's the best we can then do for a consistency model?

idea: Eventual Consistency
  client reads and writes just contact local shard
  each shard pushes writes to other datacenters, shard-to-shard, asynchronously
    that is, a put() fires off a message to each other datacenter,
    but does not wait, there could be long delays and out-of-order.

Eventual Consistency properties
  1. datacenters/clients may see updates in different orders
  2. if no writes for long enough, all clients see same data
  a pretty loose spec, many ways to implement, easy to get good performance
  used in deployed systems, e.g. Dynamo and Cassandra
  but can be tricky for app programmers

example app code -- a photo manager:
  C1 and C2 in different datacenters
  C1 uploads photo, adds reference to list:
    C1: put(photo) put(list)
  C2 reads:
    C2:                       get(list) get(photo)

what can C2 see?

app code can see non-intuitive behavior -- "anomalies"
  not incorrect, since there was no promise of better
  and it is possible to program such a system
    perhaps wait for expected data (photo) to appear
  in a bit we'll turn to COPS, which provides better behavior

how to ensure that all datacenters end up with the same value?
  if there are writes from multiple datacenters
  everyone has to choose the same final value, for eventual consistency
  
why not attach the current wall-clock time as version number on each put?
  and have all datacenters prefer higher version numbers?
  local shard server assigns v#=time when it receives client put()
  remote datacenter receives put(k, val, v#)
    if v# is larger than version of currently stored value for k
      replace with new value / v#
    otherwise
      ignore new value
  "timestamp" might be a better word here than "version"
  what if two put(k) happen at exactly the same time at different datacenters?
    break tie with a unique ID in the low bits of v#
  ok: now different datacenters will agree on final values
    so, eventually, they will become consistent

what if one datacenter's (or server's) clock is fast by an hour
  will cause that datacenter's values to win, even if an hour old!
  worse: prevents any other update for an hour!

COPS uses "Lamport clocks" to assign v#
  each server implements a "Lamport clock" or "logical clock"
    Tmax = highest v# seen (from self and others)
    T = max(Tmax + 1, wall-clock time)
  v# for a new put() is current T
  so: if some server has a fast clock, everyone who sees a version
    from that server will advance their Lamport clock

if concurrent writes, is it OK to simply discard all but one?
  the paper's "last-writer-wins"
  sometimes that's OK:
    e.g. there's only a single possible writer, so the problem can't arise
    probably I'm the only person who can write my photo list or profile
  sometimes latest-write-wins is not useful:
    what if put()s are trying to increment a counter?
    or update a shopping cart to have a new item?
  the problem is "conflicting writes"
  we'd often like to have a more clever plan to detect and merge
    mini-transactions -- atomic increment operation, not just get()/put()
    custom conflict resolution for shopping cart (set union?)
  resolution of conflicting writes is a problem for eventual/causal consistency
    no single primary to order atomic operations or transactions
  the paper mostly ignores write conflict resolution
    but it's a serious problem for real systems

can we have better consistency than eventual?
  and still retain fast local reads and writes, from any datacenter?

remember the eventual consistency anomaly with the photo list:
  C1: put(photo) put(list)
  C2:                      get(list) get(photo)
C1 and C2 in different datacenters
the problem: the put()s may arrive out of order at other datacenters.
  so get(list) may see the new photo name, but get(photo) fails
we need to enforce order on writes
  even when "photo" and "list" are in different shards

a possibility: single write log per datacenter
  each datacenter has a single "log server"
  put() appends to the local server's log, but doesn't wait
  log server sends log, in order, to other datacenters, in the background
    remote sites apply log in order
    so put(photo), put(list) will appear in that order everywhere
  two problems:
    log server will be a bottleneck
    only orders writes from this datacenter

example with writes from multiple datacenters:
  initially x=0 y=0
  C1: put(x,2)
  C2:          t=get(x) put(y,t)
  C3:                            get(y) get(x)
  C1/C2/C3 in different data centers
  suppose C2 sees x=2 (i.e. it observes C1's write)

a log per datacenter produces an anomaly for this example
  C1's put and C2's put would be in different logs, not ordered
  so C3 might see C2's put but not C1's (prior) put
    i.e. C3 might see y=2 but x=0
  we need a transitive notion of order

so:
  we want to forward puts asynchronously
  we want each shard to forward puts independently (no central log server)
  we want enough ordering to make our examples have intuitive results

here's how COPS achieves these goals

each COPS client maintains a "context" to reflect order of client ops
  client adds an item to context after each get() and put()
  client tells COPS to order each put() after everything in its context
  C2's get(x) yields version v2
    C2's context now: x/v2
  C2's put(y,2)
    C2 sends put(y,2,x/v2) to local shard server
  local shard server for y:
    picks a new v# = 3 for y,
    stores y, 2, v3
    sends y,2,v3,x/v2 to corresponding shard server in each datacenter
      but does not wait for reply
  remote shard server receives y,2,v3,x/v2
    talks to local shard server for x
      *waits* for x to reach version v2 (from C1's datacenter)
    then updates DB to hold y,2,v3
    
COPS calls a relationship like "y/v3 comes after x/v2" a "dependency"
  x/v2 -> y/v3

what does a dependency imply for COPS?
  if C3 sees y/v3, then asks for x, it should see at least x/v2
  this notion of dependency is meant to match programmer intuition
    about what it means to get(x) AND THEN put(y)
    or put(x) AND THEN put(y)

these consistency semantics are called "causal consistency"
  paper defines in Section 3 / Figure 2
  a client establishes dependencies between versions in two ways:
    1. its own sequence of puts and gets ("Execution Thread" in Section 3)
    2. reading data written by another client
  dependencies are transitive (if A -> B, and B -> C, then A -> C)
  the system guarantees that if A -> B, and a client reads B,
    then the client must subsequently see A (or a later version)

causal consistency makes the photo list example work
  put(list) will arrive with photo as a dependency
  remote servers will wait for photo to appear before installing updated list

nice: when updates are causally related, readers see versions
  at least as new as the writer saw.

nice: when updates are NOT causally related, COPS has no order obligations
  example:
    C1: put(x,1)
    C2:          put(y,2)
    C3:                   put(x,3)
  these are not causally related
  so they can appear in different orders at different datacenters
  no need for any mechanisms to enforce agreement on order of appearance
    e.g. no single primary for x
    e.g. no wait for write to complete as in linearizability
  we can expect this freedom to help performance

but: readers may see newer data than required by causal dependencies
  so we're not getting transactions or snapshots 

but: COPS sees only certain causal relationships
  ones that COPS can observe from client get()s and put()s
  if there are other communication channels, COPS is only eventually consistent
  e.g. I put(k), tell you by phone, you do get(k), maybe you won't see my data

COPS optimizations avoid ever-growing client contexts
  * client clears context after put(x), replaces with x/v#
    so next put(), e.g. put(y), depends only on x/v#
    so remote sites will wait for arrival of x/v# before writing y
    x/v# itself was waiting for (cleared) context
    so y effectively also waits for (cleared) context
  * garbage collection sees when all datacenters have a certain version
    that version never needs to be remembered in context
    since it's already visible to everyone

are there situations where ordered puts/gets aren't sufficient?
  yes: when you need transactions or atomic update
  paper's example: a photo list with an ACL (Access Control List)
  get(ACL), then get(list)?
    what if someone deletes you from ACL, then adds a sensitive photo?
      between the two get()s
  get(list), then get(ACL)?
    what if someone deletes sensitive photo, then adds you to ACL?
  need a multi-key get that returns mutually consistent versions

COPS-GT get_trans() provides read-only sort-of transactions
  servers store full set of dependencies for each value
  servers store a few old versions of each value
  get_trans(k1,k2,...)
    client library does independent get()s
    get()s return dependencies as well as value/v#
  client checks dependencies
    for each get() result R,
      for each other get result S mentioned in R's dependencies,
        is S/v#  >= version mentioned in R's dependency?
  if yes for all, can use results
  if no for any, need a second round of get()s for values that were too old
    each fetches the version mentioned in dependencies
    may be old: to avoid cascading dependencies

for ACL / list example:
  C1: get_trans(ACL, list)
  C1: get(ACL) -> v1, no deps
      C2: put(ACL, v2)
      C2: put(list, v2, deps=ACL/v2)
  C1: get(list) -> v2, deps: ACL/v2
  (C1 checks dependencies against value versions)
  C1: get(ACL,v2) -> v2
  (now C1 has a causally consistent pair of get() results)

why are only two phases needed for COPS-GET get transactions?
  a new value won't be installed until all its dependencies are installed
  so if a get() returns a dependency, it must already be locally installed

performance?
  Section 6.2:
    one client, a single server in each datacenter
    52,000 gets per second
    30,000 puts per second (async forwarding to remote datacenter)
  that is OK performance, like a conventional DB
  but no comparisons with other systems
    not for performance
    not for ease of programming
  too bad, since central thesis is that COPS has a better tradeoff between
    ease of programming and performance

limitations / drawbacks, for both COPS and causal consistency
  conflicting writes are a serious difficulty
  awkward for clients to track causality
    e.g. user and browser, multiple page views, multiple servers
  COPS doesn't see external causal dependencies
    s/w and people really do communicate outside of the COPS world
  limited notion of "transaction"
    only for reads (though later work generalized a bit)
    definition is more subtle than serializable transactions
  significant overhead
    track, communicate, enforce causal dependencies
    garbage collection
  update delays can cascade

impact?
  causal consistency is a popular research idea
    with good reason: promises both performance and useful consistency
    much work before COPS -- and after (Eiger, SNOW, Occult)
  causal consistency is rarely used in deployed storage systems
  what is actually used?
    no geographic replication at all, just local
    primary-site (PNUTS, Facebook/Memcache)
    eventual consistency (Dynamo, Cassandra)
    strongly consistent (Spanner)
