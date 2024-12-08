---
title: invariant-pyramid
date created: Thursday, December 5th 2024, 10:21:05 pm
date modified: Thursday, December 5th 2024, 10:36:06 pm
---

The invariant pyramid constitutes of:

1. Program (What invariants your program enforces, either at compile time or runtime)
2. Tests (What invariants your tests enforce)
3. Documentation (What invariants are enforced outside of the code)
4. Unknown (What invariants are out there but not captured)

These go from strongest to weakest, where having more invariants captured in the program > tests > documentation.

You want few invariants that are unknown, and want to hoist most of the invariants as high up as you can.