---
title: looping-in-bash
---

In Bash

# Looping in Bash

## Basic loops

In bash, looping can be done like so:

```sh
for i in **/*.md; do
  # do something with i
done
```

This lets us set get the value of every iteration, but we can\'t access
the index.

## Looping with Index

Assuming we have an array of items, and we want to get the index of
their items as well:

```sh
items=(10,20,30)
for i in ${!items[@]}; do
  echo "Key: $i"
  echo "Value: ${allThreads[$i]}"
done
```

## Calculating Array Length

Array lengths can be calculated like so:

```sh
items=(10, 20, 30)
${#items[@]}
```
