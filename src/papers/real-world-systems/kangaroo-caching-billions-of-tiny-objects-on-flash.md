---
title: "Kangaroo Caching Billions Of Tiny Objects On Flash"
pdf_url: "[[kangaroo-caching-billions-of-tiny-objects-on-flash.pdf]]"
---
This paper introduces Kangaroo, a flash cache design for billions of tiny objects that keeps DRAM usage low, and flash write amplification low.

## The Problem

- Large services maintain large working sets of tiny objects. These don't fit in DRAM, and are well suited for flash.
- But flash writes are page-sized, i.e. 4KB. A 100B object would require persisting a 4KB page, which gives a write application of 40x.
- Flash has limited write endurance due to write amplification.
- Indexing billions of objects is DRAM-expensive.

Some existing approaches solve half the problem:

1. Log-structured flash cache is good for write amplification, but bad for DRAM.
2. Set-associative flash caches are good for DRAM, but bad for write amplification.

## Kangaroo's Design

Kangaroo combines both of these ideas hierarchically. 

1. Tiny DRAM cache: (~1%) - in front, for ultra-hot objects.
2. KLog: (~5%) - stores objects in a circular log on flash.
3. KSet: (~95%) - A large set-associative cache on flash. Objects are mapped by hash to a fixed page. There is no indexing, and each set has a bloom filter and eviction.

Items start in KLog and can move to the DRAM cache or Kset based on how hot they are.


## KLog's purpose: write-efficient staging with an index

- Index entries contain the offset, tag, next pointer, eviction metadata, a valid bit.
- The index is partitioned. 
- The Klog's writes are batched to be saved in KSet.

## KSet

- Items from KLog are buffered until multiple objects can be batched to the same KSet in one write on a page.

Eviction looks like this:

 A background thread flushes KLog segments
- For each victim entry:
	1. Collect all KLog objects mapping to the KSet.
	2. If at least $n$ objects, (the threshold) are found, move them in one write.
	3. Otherwise, drop them or re-admit popular ones back to KLog.

## Results

Compared to a set-associate small object cache and an optimistic log-structured cache with DRAM index:

Kangaroo uses flash capacity better and cuts caches misses over both.

The main takeaway is that a small front layer (KLog) to batch and co-locate writes, with a large set-associate back layer (KSet) with the right admission and eviction scheme can go far.