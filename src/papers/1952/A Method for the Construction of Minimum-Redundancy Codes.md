---
title: A Method for the Construction of Minimum-Redundancy Codes
author:
  - "David Huffman"
doi: "10.1109/jrproc.1952.273898"
url: "https://doi.org/10.1109/jrproc.1952.273898"
pdf_url: "[[A Method for the Construction of Minimum-Redundancy Codes.pdf]]"
is_oa: false
date created: Saturday, July 19th 2025, 11:05:43 pm
date modified: Sunday, July 20th 2025, 10:16:31 am
---

# A Method for the Construction of Minimum-Redundancy Codes

Huffman, a graduate student at MIT in 1952, published this paper to outline what became known as Huffman coding, the most efficient binary code. Fano, his teacher, worked with Shannon to create Shannon-Fano coding, which used a top-down binary tree to create their own encoding. Huffman coding uses bottom-up encoding, which is provably optimal.

```python
from collections import Counter
from heapq import heapify, heappop, heappush
from dataclasses import dataclass
from typing import Optional

@dataclass
class Node:
    ch: Optional[str]
    freq: int
    left: Optional['Node'] = None
    right: Optional['Node'] = None

    def __lt__(self, other):
        return self.freq < other.freq

def get_huffman_tree(text):
    if not text:
        return
    freq = Counter(text)
    pq = [Node(k, v) for k, v in freq.items()]
    heapify(pq)
    while len(pq) > 1:
        left, right = heappop(pq), heappop(pq)
        new_freq = left.freq + right.freq
        heappush(pq, Node(None, new_freq, left, right))
    return pq[0]

print(get_huffman_tree('AADDDDDBBBE'))
```