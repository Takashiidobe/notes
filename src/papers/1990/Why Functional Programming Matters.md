---
title: Why Functional Programming Matters
date created: Sunday, July 27th 2025, 9:16:43 am
date modified: Sunday, July 27th 2025, 3:49:22 pm
author:
  - John Hughes
url: https://dl.acm.org/doi/10.5555/119830.119832
pdf_url: "[[Why Functional Programming Matters.pdf]]"
---


# Why Functional Programming Matters

Functional Programming is about writing a program that applies functions to arguments. Therefore, they are side-effect free. A function can be evaluated at any time, and can be replaced by variables that return its values.

Functional programming allows programs to be glued together easier, since they don't rely on mutable state passing. I/O or any mutation can be removed from modules as much as possible and only put in at the end, allowing for easier mutation.

The author goes through an example in functional programming (lazy languages, like haskell) have over conventional programs. They can be used to define a search tree and then iterate through it, only requiring as much memory to compute the next move. In a usual programming language, you would have to build and check all the previous paths, which would quickly lead to running out of memory.