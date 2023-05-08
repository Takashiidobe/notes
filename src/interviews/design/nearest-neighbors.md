# Nearest Neighbor Search in high dimensional space

Deep learning has transformed search -- we use semantic similarity by encoding words into some N dimensional space, where objects that are nearby are more likely semantically similar. (Dog and cat are closer in 5-dimensional space here).

Dog: (0, 1, 23, -12, 20)
Cat: (2, 1, 19, -7, 22)
Car: (20, -10, -5, -12, 10)
Ship: (16, -13, 0, -8, 12)
Sailor: (12, -4, 4, -12, 15)

Each point is then embedded in some 100 dimensional plane, and queries are hashed to the same plane, and then queried for top-k nearest neighbors.

There are two main problems:

1. Existing algorithms use in-memory indicies for sub-10ms latency, which is extremely expensive
2. Indices cannot be updated efficiently, which requires them to be rebuilt every so often. They also become stale due to updates not be reflected in the index.

At a large enough scale, this would require 10s of thousands of machines, which would cost millions of dollars more a month.

This system uses ANNs (Artificial Neural Networks) to create a fast greedy search from one point to another point, which can be used to output the k-nearest neighbors with some error. This, however, uses an in-memory data structure, which is too expensive.

Microsoft optimized DiskANN, an ANN on disk, where compressed vectors are saved to SSD, and each hop between queries is a read from the SSD. There is an in-memory representation of the index as well, which can accept updates and serializes them to disk periodically. This allows for fast updates without staleness.
