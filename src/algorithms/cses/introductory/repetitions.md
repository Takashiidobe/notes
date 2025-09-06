---
title: Repetitions
date created: Monday, July 21st 2025, 7:07:34 am
date modified: Monday, July 21st 2025, 8:00:31 am
---

# Repetitions

Prev: [missing-number](missing-number.md) Next:
[increasing-array](increasing-array.md)

You are given a DNA sequence: a string consisting of characters `A`, `C`, `G`, and `T`.  
Your task is to find the **longest repetition** in the sequence — that is, the maximum-length substring containing only one type of character.

## Input

The only input line contains a string of length $n$.
## Output

Print one integer: the length of the longest repetition.

## Constraints

$$1 \le n \le 10^6$$
## Example

**Input**

```
ATTCGGGA
```

**Output**

```
3
```
## Answer

We want to calculate the longest sequence of repetitions, so we increment our count of length if it matches the previous character, otherwise, we reset the count to 0 and keep our previous character as the character we're looking for.

```cpp
#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::string s;
    std::cin >> s;

    int max_len = 1, cur_len = 1;

    for (size_t i = 1; i < s.size(); i++) {
        cur_len = (s[i] == s[i - 1]) ? cur_len + 1 : 1;
        max_len = std::max(max_len, cur_len);
    }

    std::cout << max_len << '\n';
}
```

Prev: [missing-number](missing-number.md) Next:
[increasing-array](increasing-array.md)
