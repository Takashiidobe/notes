---
title: Comby
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Tuesday, November 12th 2024, 8:40:37 pm
---

# Comby

Comby is a tool for Refactoring codebases in any language:
[Comby](https://github.com/comby-tools/comby.md)

## Installation:

on Mac OS: `brew install comby`

## Usage:

Comby live allows you to run an interactive version and generate a
query:

[Comby Live](https://comby.live/)

## Example:

Replace `std::cout << something << std::endl;` with `fmt::print`.

```sh
comby \'std::cout \<\< :\[expr\] \<\< std::endl;\' \'fmt::print(\"{}\",
:\[expr\])\' .cc -i
```
