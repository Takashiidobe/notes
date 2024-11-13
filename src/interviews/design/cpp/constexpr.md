---
title: Constexpr
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Tuesday, November 12th 2024, 7:07:30 pm
---
# Constexpr

`Constexpr` is a keyword in C++ that allows the compiler to generate some code at compiler time and inject it into the static part of your executable.

It transparently allows code that is not `constexpr` to still compile -- it would generate that code at runtime, however.

It can also be used in branches with `if constexpr`, where it only compiles a branch for the code that can be verified at compile time to take one branch.
