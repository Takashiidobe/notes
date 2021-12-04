---
title: hashmaps-in-bash
---

In Bash

# Hashmaps in Bash

Use the declare keyword in bash to create a hashmap in bash.

```sh
declare -A hashmap
hashmap["key"]="value"
hashmap["key2"]="value2"
echo "${hashmap["key"]}"
for key in ${!hashmap[@]}; do
    echo $key;
done
for value in ${hashmap[@]}; do
    echo $value;
done
echo hashmap has ${#hashmap[@]} elements
```
