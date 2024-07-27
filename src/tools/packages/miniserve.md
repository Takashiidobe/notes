---
title: miniserve
---

# Miniserve

Miniserve is a simple utility that serves files and directories over
http.

## Installation

```sh
brew install miniserve
```

```sh
cargo binstall miniserve
```

## Usage

Serve a directory:

```sh
$ miniserve path/to/directory
```

Serving `$PWD` on the current port with an index file.

```sh
$ miniserve . --port=3000 --index index.html
```

Serve a single file:

```sh
$ miniserve path/to/file
```

Serve a directory using HTTP basic authentication:

```sh
$ miniserve --auth username:password path/to/directory
```
