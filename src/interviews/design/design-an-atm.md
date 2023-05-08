# Design an ATM

We're going to be designing an ATM.

The interface is going to be simple. A user can deposit/withdraw/send/check
money in their bank account, after attesting their identity.

The system prioritizes high availability and consistency (what use is a
financial network if I can't access my finances?) and losing people's
money is a criminal offense, so we can't do that.

What happens in case of a network partition?

What sort of system would you create, and what are the tradeoffs?

## Feedback

I said on average: so we might have spikes - it's good for an average
reading, but reads and writes might spike at any time. Good to think
about that (bank runs).

Denormalizing to deal with balance + transactions table. We could use a
materialized view/view to not have to denormalize and create faster
reads when reading.

Serialize everything, since we're running into data races, or Repeatable
Read.

Could we keep the other transactions into cold storage?

What happened to the id generation service?

## System

Let's assume that ATMs are a frontend to some backend system that takes
a lock on a user's balance when a user wants to do a mutating operation.

What sort of concurrency primitives would you use for this?

Make sure to discuss Back of the Envelope numbers (how many transactions
should we expect at a specific time? What problems does this make?)

(Visa has a TPS of about 1.7k, so that's all we need to do).

## Allowing Reads/Writes in a System

What isolation level should we allow for this system? What is the
tradeoff that makes? Could you write an SQL query/draw a data schema for
this?

Is there a problem if a phantom read occurs?

- A phantom read occurs when, in the course of a transaction, new rows are added or removed by another transaction to the records being read.

Do we need multi-object transactions?

- What happens if you want to send money to multiple people? Shouldn't
  that fit in a transaction (what happens if I split the transaction
  into pieces?)

- Any reason we should pick one or the other?

### Possible Isolation levels

(Consistency)

- Serializable requires that all transactions are totally orderable.
  This means readers and writers block each other. Also during a network partition,
  nodes cannot make progress. This also has a huge performance penalty
  (probably too slow). This also doesn't work on multi-object
  transactions.

- Strict Serializable requires that all transactions on multi-objects
  are totally orderable. Doesn't work during network partitions, and has
  a huge performance penalty (probably too slow).

(Availability - Can make progress if some nodes are down).

- Read Committed. Transactions are not allowed to observe writes from
  transactions which do not commit. This can make progress if some nodes
  are down. This allows non-repeatable reads (a user queries a row and
  then later queries the same row, only to discover the data has
  changed in the transaction).

```sql
BEGIN;

SELECT balance from accounts where id = 1; -- (make sure balance is >
balance required)

-- During this transaction, another transaction happens:
BEGIN;
UPDATE accounts set balance = 0 where id = 1;
COMMIT;
-- Now the id has a balance of 0

SELECT balance from accounts where id = 1; -- Balance is now 0. If we
make a transaction, it'll set the balance negative. Is this Ok?

COMMIT;
```

What are some pros and cons of the consistent way? What are some pros
and cons of the available way? What can we do to solve the problems of
each?

## Consistency

- If one node is down and we choose an algorithm that cannot make
  progress if a node is down, we may get a backlog of transactions that
  need to be done later on (are queued). How do we deal with this?

## Availability

- If we choose a highly available setup, we might have accounts with
  negative money, or other non-desirable states. What should we do in
  this case?
