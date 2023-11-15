---
title: fundamentals-of-shared-libraries
---

# Fundamentals of Shared Libraries

Prev: [login-accounting](login-accounting.md) Next: [advanced-features-of-shared-libraries](advanced-features-of-shared-libraries.md)

## Object Libraries

Normally to save on compilation time, we create object files that are registered with make, so they are only compiled when the underlying `.c` file changes.

```sh
cc -g -c prog.c mod1.c mod2.c mod3.c
cc -g -o prog_nolib prog.o mod1.o mod2.o mod3.o
```

However, if libraries are to be bundled for more than one user, we need a better approach. There are two types of libraries: static and shared.

## Static Libraries

Static libraries, also called archives, with the format `libname.a` were the first type. They use the command `ar`:

`ar options archive object-file...`

`ar` adds object files together so they can be treated as one unit.

Some common commands include:

- `r`: replace: insert an object file into the archive.

```sh
cc -g -c mod1.c mod2.c mod3.c
ar r libdemo.a mod1.o mod2.o mod3.o
rm mod1.o mod2.o mod3.o
```

- `t`: table of contents: list the object files the archive contains: (v is for verbose).

```sh
ar tv libdemo.a
rw-r--r-- 1000/100 1001016 Nov 15 12:26 2009 mod1.o
rw-r--r-- 1000/100 406668 Nov 15 12:21 2009 mod2.o
rw-r--r-- 1000/100 46672 Nov 15 12:21 2009 mod3.o
```

- `d` (delete) Delete a named module from the archive:

```sh
ar d libdemo.a mod3.o
```

### Using a static library

Static libraries can be used in the following way:

By explicitly naming the library:

```sh
cc -g -c prog.c
cc -g -o prog prog.o libdemo.a
```

If the library is located in a standard location, like `/usr/lib`, then the name of the library can be specified with `-l`.

```sh
cc -g -o prog prog.o -ldemo
```

If the library resides in a directory not normally searched by the linker, we can
specify that the linker should search this additional directory using the –L option:

```sh
cc -g -o prog prog.o -Lmylibdir -ldemo
```

## Shared Libraries

When a static library is built, copies of the code provided by the object code are loaded into memory. This has benefits (no runtime dependency on a library) but also some cons, like increasing memory usage as each process will need to load in the code into memory separately, as well as having slower upgrades on security dependencies (like libssl).

Prev: [login-accounting](login-accounting.md) Next: [advanced-features-of-shared-libraries](advanced-features-of-shared-libraries.md)
