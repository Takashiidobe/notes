---
title: Map Vs Unordered Map
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Tuesday, November 12th 2024, 7:07:45 pm
---
# Map Vs Unordered Map

Map is an ordered TreeMap (RBTree) and UnorderedMap is a hashmap.

UnorderedMap is forced by the standard to use a bucketing approach, which makes it perform poorly (cache wise).

To make performance better, a absl::dense_hash_map might be better, since it uses open addressing instead of separate chaining.

You can also have a hybrid approach (chaining + open addressing) to increase cache locality and have less iterator invalidation.
