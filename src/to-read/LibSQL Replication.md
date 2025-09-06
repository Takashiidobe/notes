---
title: "LibSQL Replication"
source: "https://blog.canoozie.net/libsql-replication/"
author:
  - "[[Jeremy Tregunna]]"
published: 2025-05-23
created: 2025-07-20
description: "Have you ever looked at something and thought, \"Yeah, that's the right way to do it\"? Because that's how I felt when digging into the replication architecture of LibSQL when I was adding replication to Kevo.If you don't care about the article and just want the TL;DR, then"
tags:
  - "clippings"
---
Have you ever looked at something and thought, "Yeah, that's the right way to do it"? Because that's how I felt when digging into the replication architecture of [LibSQL](https://turso.tech/libsql?ref=blog.canoozie.net) when I was adding replication to [Kevo](https://github.com/KevoDB/kevo?ref=blog.canoozie.net).

If you don't care about the article and just want the TL;DR, then you can skip to that. Now let's jump right into it.

## Frames

In LibSQL's replication system, frames are the fundamental unit of replication and each frame represents a change to a single database page. Structurally, a frame is made up of a few things:

- A `FrameHeader` which includes:
	- `frame_no` which is a monotonically increasing number
	- `checksum` A CRC-64 integrity checksum, more on this later
	- `page_no` is the database page this frame changes
	- `size_after` is non-zero only if this frame is part of a commit
- Page data, which is 4KB of raw disk changes

Frames get logged into the write-ahead log (WAL), sent, received, and replayed. The WAL is the authoritative source of all database changes, and so naturally, intercepting these frames helps us build replication between the primary, that receives all the writes, to all the replicas, which can be used to ensure none of your reads get blocked by a write.

## Checksums

This is where things get clever, so I hope you find this interesting.

Instead of using a checksum to just generate a number that can be checked to ensure the data hasn't been modified in a frame, the way LibSQL goes about it uses what's known as a **rolling checksum**. A rolling checksum is calculated using the current frame's data, of course, but also the checksum from the previous frame.

That means that each frame is cryptographically chained to the one before it. If someone--or something--messes with even one byte of page data anywhere in the history, that change cascades forward and breaks the whole chain.

If you're familiar with git, this works the same way, and while not novel, it is brilliant for a few reasons.

### Why it matters

You want to know your data is good, right? Just check the latest checksum. If it checks out, you're golden--because that implies every previous frame was not tampered with too, so you don't need to scan the whole file, byte by byte. It's like verifying a blockchain: tamper with anything and the chain breaks.

But this isn't security theater, it's not some feel good hash that no one ever checks... this checksum is used every time a frame is committed or replicated. If you're a replica, and your frame stream doesn't line up? You reject it. You're done. That's the kind of hard-stop safety you want in a distributed system.

They're predictable.  
They're fast.  
They're cheap to compute.  
They're incremental, you don't need to recompute from scratch.

## Lessons from an age gone by

As someone who's been around since the days when we wrote our own journaling systems because file systems were unreliable (you probably haven't experienced these kinds of problems, but they were more common decades ago), I appreciate when a system avoids unnecessary complexity. LibSQL's approach here is lean, not clever, and smart (as in it'll still make sense a decade from now).

## TL;DR

- **Frames** are the atomic unit of change in LibSQL's replication
- **Rolling checksums** give you a tamper proof chain of changes that when modified, becomes very clear it's been tampered with
- It's **fast**, **reliable**, and incredibly **effective** for streaming replication
- It's another example of LibSQL building on SQLite's base without adding **unnecessary complexity**

If you're designing replication or journaling in any kind of system, whether embedded, distributed, edge, whatever, take a note from LibSQL's rolling checksums; it might just save you a few sleepless nights.