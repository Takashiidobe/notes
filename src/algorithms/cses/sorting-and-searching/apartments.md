---
title: apartments
---

# Apartments

Prev: \[distinct-numbers](distinct-numbers.md)
Next: \[ferris-wheel](ferris-wheel.md)

There are n applicants and m free apartments. Your task is to distribute
the apartments so that as many applicants as possible will get an
apartment.

Each applicant has a desired apartment size, and they will accept any
apartment whose size is close enough to the desired size.

Input

The first input line has three integers n, m, and k: the number of
applicants, the number of apartments, and the maximum allowed
difference.

The next line contains n integers a1,a2,\...,an: the desired apartment
size of each applicant. If the desired size of an applicant is x, he or
she will accept any apartment whose size is between x−k and x+k.

The last line contains m integers b1,b2,\...,bm: the size of each
apartment.

Output

Print one integer: the number of applicants who will get an apartment.

## Explanation

We want to match applicants to apartments within a range of k. To do
this, we\'ll sort both the apartments and residents, and put a pointer
in both arrays.

If we find that the absolute difference between the person\'s want and
the apartment size is below k, we\'ve found a match. Increment the
answer, and move onto the next person and apartment.

If we don\'t find a match, it could be because of two reasons: If the
person\'s want is smaller than the apartment\'s size, then we move onto
the next person to see if they\'re a fit.

Otherwise, if the apartment size is too small, we move onto the next
apartment, because the same person might want the next biggest
apartment.

This greedy solution works because we\'ve sorted; when we are at person
i or apartment j, we know already that there are no persons i that could
want apartment j, because their wants are smaller than person\[i\].

## Solution

```cpp
{{# include _include/code/algorithms/cses/cpp/sorting-and-searching/apartments.cc }}
```

Prev: \[distinct-numbers](distinct-numbers.md)
Next: \[ferris-wheel](ferris-wheel.md)
