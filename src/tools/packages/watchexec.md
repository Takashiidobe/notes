---
title: watchexec
---

# Watchexec

Watchexec is a utility that runs a command when files are modified.

## Installation

Install watchexec on Mac with:

```sh
brew install watchexec
```

## Running

To send a SIGKILL signal to stop the child process before rerunning the
command:

`watchexec -n -s SIGKILL ${server-command}`

To run make when any file in `lib` or `src` changes:

```sh
watchexec -w lib -w src make
```
