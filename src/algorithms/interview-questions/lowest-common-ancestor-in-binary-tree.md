---
title: lowest-common-ancestor-in-binary-tree
---

Common Ancestor in a Binary Tree\"

# Lowest Common Ancestor in a Binary Tree

Prompt:

Given two people, how can we find out if they are blood related?

Questions:

- Do we assume that our reporting is accurate, ie are there are only
  two parents for every person?
- Could there be more than two or less than two (In the case there are
  more parents that claim a child/parents that don\'t claim a child).

Modeling:

- How do we uniquely identify the nodes? We can\'t use names, because
  names are non-unique. Maybe use some UUID?

```py
class Node:
  def __init__(self, name, parents = []):
    self.name = name
    self.uuid = UUID.new()
    self.parents = parents
```

- Do we get a root pointer to the root of the tree?

We need to check the
