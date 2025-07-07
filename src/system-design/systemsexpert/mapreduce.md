---
title: Mapreduce
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Sunday, July 6th 2025, 8:41:42 pm
---

# Mapreduce

Mapreduce is used for large datasets that need to be processed. If one
machine can\'t process all the data, you\'ll have to split the workload
across many machines, and handle haradware failure, network partitions,
and software failure.

Mapreduce only requires you to define two steps: `map` and `reduce`. Map
applies some computation to each element in the set, and reduce
aggregates the set into one value.

Every value must be a `key-value` pair. All keys with the same `key` are
given to the same machine, and sorted by the machine. Then the library
reduces according to logic you gave it, and outputs one result per key,
or for the whole dataset.

Mapreduce handles machines failing and network partitions for you, which
allows you to focus abstractly on the computation, rather than how it\'s
done.

Prev:
\[publish-subscribe-pattern](publish-subscribe-pattern.md)
Next:
\[security-and-https](security-and-https.md)
