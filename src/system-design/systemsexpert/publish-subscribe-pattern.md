---
title: publish-subscribe-pattern
---

Subscribe Pattern

# Publish Subscribe Pattern

    Publishers   Topics   Subscribers
    [ P ]------->[ T ]<----->[ S ]

Publishers publish messages to Topics.

Subscribers listen to those Topics.

Topics send out messages to the Subscribers.

When a message is received by a Subscriber, it is acked to the Topic, so
the Topic knows it can remove it from the queue.

When the message is processsed by the Subscriber, there is a callback
sent back to the Publisher, so the Publisher knows when the job was
completed.

Topics will try to send messages at least once \-- your messages might
be processed more than once.

## Idempotency

An idempotent operation has the same effect, even if it is executed more
than once.

Because PubSub has guaranteed at least once delivery, you need to have
some way to guard against messages being sent more than once.

executing this command 5 times will set the count to 5, 5 times. This is
ok.

    SET count 5

meanwhile this command being set 5 times will change the value of count
5 times.

    INCR count 1

## Queueing

Topics can guarantee some ordering of events, even distributed.

## Tools

Google Cloud PubSub, SQS, Kafka

Prev:
\[logging-and-monitoring](logging-and-monitoring.md)
Next: \[mapreduce](mapreduce.md)
