---
title: Build for Different Architectures in Go
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Wednesday, November 13th 2024, 7:01:46 am
---

# Build for Different Architectures in Go

Go programs can be built for different architectures and Operating
systems using the \$GOOS environment variable and the \$GOARCH
variables.

For example, for 32-bit Linux:

`GOOS=linux GOARCH=386 go build -o linux_386_build`

## List of Options

| \$GOOS   | \$GOARCH |
| -------- | -------- |
| aix      | ppc64    |
| android  | 386      |
| android  | amd64    |
| android  | arm      |
| android  | arm64    |
| darwin   | 386      |
| darwin   | amd64    |
| darwin   | arm      |
| darwin   | arm64    |
| dragonfl | y amd64  |
| freebsd  | 386      |
| freebsd  | amd64    |
| freebsd  | arm      |
| illumos  | amd64    |
| js       | wasm     |
| linux    | 386      |
| linux    | amd64    |
| linux    | arm      |
| linux    | arm64    |
| linux    | ppc64    |
| linux    | ppc64le  |
| linux    | mips     |
| linux    | mipsle   |
| linux    | mips64   |
| linux    | mips64le |
| linux    | s390x    |
| netbsd   | 386      |
| netbsd   | amd64    |
| netbsd   | arm      |
| openbsd  | 386      |
| openbsd  | amd64    |
| openbsd  | arm      |
| openbsd  | arm64    |
| plan9    | 386      |
| plan9    | amd64    |
| plan9    | arm      |
| solaris  | amd64    |
| windows  | 386      |
| windows  | amd64    |
