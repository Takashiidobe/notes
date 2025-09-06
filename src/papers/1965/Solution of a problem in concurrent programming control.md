---
title: Solution of a Problem in Concurrent Programming Control
author:
  - "E. W. Dijkstra"
doi: "10.1145/365559.365617"
url: "https://doi.org/10.1145/365559.365617"
pdf_url: "[[Solution of a problem in concurrent programming control.pdf]]"
is_oa: true
date created: Sunday, July 20th 2025, 10:47:15 am
date modified: Sunday, July 20th 2025, 10:47:39 am
---

# Solution of a Problem in Concurrent Programming Control

Assume there are N computers which engage in a cyclic activity.

The computers engage with a common store where they can write or read to (but not at the same time).

## The Problem

1. The solution must be symmetrical. There is no static ordering of the computers (i.e. if 1 and 2 are trying to use the store, there is no previous ordering that says 1 should beat out 2 in case of ties. If there is, this problem is trivial).
2. The speeds of the computers are unknown.
3. If a computer is stopped outside of its critical section, this should not block other computers.
4. There should be no deadlock, where two computers spin forever, each waiting for the other.

## The Solution

The solution proposes a common store where

## The Proof