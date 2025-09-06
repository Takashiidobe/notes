---
paper id: 1512.00727v2
title: "TinyLFU: A Highly Efficient Cache Admission Policy"
authors: Gil Einziger, Roy Friedman, Ben Manes
publication date: 2015-12-02T15:05:46Z
abstract: "This paper proposes to use a frequency based cache admission policy in order to boost the effectiveness of caches subject to skewed access distributions. Given a newly accessed item and an eviction candidate from the cache, our scheme decides, based on the recent access history, whether it is worth admitting the new item into the cache at the expense of the eviction candidate.   Realizing this concept is enabled through a novel approximate LFU structure called TinyLFU, which maintains an approximate representation of the access frequency of a large sample of recently accessed items. TinyLFU is very compact and light-weight as it builds upon Bloom filter theory.   We study the properties of TinyLFU through simulations of both synthetic workloads as well as multiple real traces from several sources. These simulations demonstrate the performance boost obtained by enhancing various replacement policies with the TinyLFU eviction policy. Also, a new combined replacement and eviction policy scheme nicknamed W-TinyLFU is presented. W-TinyLFU is demonstrated to obtain equal or better hit-ratios than other state of the art replacement policies on these traces. It is the only scheme to obtain such good results on all traces."
comments: "A much earlier and shorter version of this work appeared in the
  Euromicro PDP 2014 conference"
pdf: "[[papers/arxiv/TinyLFU A Highly Efficient Cache Admission Policy (1512.00727v2).pdf]]"
url: https://arxiv.org/abs/1512.00727v2
tags: []
---
