---
title: _index
---

# Introduction

## Creating Executable Binaries

- The compiler turns `cpp` files into `object` files, `.o` files.
- The linker `ld` then links in other libraries and the C++ standard
  library before creating the binary.

## Debug vs Release

- You may choose to create debug versions of your source code that
  compile faster, but for release, you should be using flags like
  `-O3` for best optimization.
