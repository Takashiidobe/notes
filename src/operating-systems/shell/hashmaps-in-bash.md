---
title: Hashmaps in Bash
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Tuesday, November 12th 2024, 8:30:51 pm
---

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
