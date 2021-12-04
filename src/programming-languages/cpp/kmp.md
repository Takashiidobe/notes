---
title: kmp
---

# KMP String.contains in O(n) time.

Instead of doing the naive O(nm) algorithm, we can go back to the
longest suffix that is a prefix.

This lets us avoid extra work.

We need to create a prefix + suffix array:

take dsgwadsgz:

d s g w a d s g z \[0,0,0,0,0,1,2,3,0\]

```cpp
int kmp(const string &t, const string &p) {
  if (p.empty()) { return 0; }

  vector<int> pi(p.size(), 0);
  for (int i = 1, k = 0; i < p.size(); i++) {
    while (k && p[k] != p[i]) {
      k = pi[k-1];
    }
    if (p[k] == p[i]) { k++; }
    pi[i] = k;
  }

  for (int i = 0, k = 0; i < t.size(); i++) {
    while (k && p[k] != t[i]) {
      k = pi[k-1];
    }
    if (p[k] == t[i]) {
      k++;
    }
    if (k == p.size()) {
      return i - k + 1;
    }
  }

  return -1;
}
```
