---
title: jenv
---

`Jenv` is a java package manager.

Install it with `brew install jenv`.

Let\'s say you have two different JDK versions, 16 and 8.

```sh
adoptopenjdk-16.jdk
adoptopenjdk-8.jdk
```

You\'ll want to add each JVM to jenv.

```sh
jenv add /Library/Java/JavaVirtualMachines/adoptopenjdk-16.jdk/Contents/Home/
```

```sh
jenv add /Library/Java/JavaVirtualMachines/adoptopenjdk-8.jdk/Contents/Home/
```

Then, `jenv versions` should list both versions.

```sh
  system
  1.8
  1.8.0.282
* 16 (set by /Users/takashi/.jenv/version)
  16.0
  16.0.1
  openjdk64-1.8.0.282
  openjdk64-16.0.1
```

You can globally set your default java version with
`jenv global (version)`

`jenv global 16` would set the default jdk to 16.
