---
title: A Method for the Construction of Minimum-Redundancy Codes
date created: Wednesday, October 4th 2023, 10:25:54 am
date modified: Saturday, December 7th 2024, 8:35:37 pm
---

# A Method for the Construction of Minimum-Redundancy Codes

Huffman, a graduate student at MIT in 1952, published this paper to outline what became known as Huffman coding, the most efficient binary code. Fano, his teacher, worked with Shannon to create Shannon-Fano coding, which used a top-down binary tree to create their own encoding. Huffman coding uses bottom-up encoding, which is provably optimal.


```py
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
