---
title: Cross Compiling C for Android
date created: Sunday, December 15th 2024, 10:51:21 pm
date modified: Sunday, December 15th 2024, 10:54:48 pm
---

# Cross Compiling C for Android

1. To cross compile for android, you'll need a recent version of the NDK linked and in your $PATH. Download it here: [Download](https://developer.android.com/ndk/downloads)
2. Next, Unzip it in some location, e.g. $HOME.
3. Add this path to your $PATH, so you can use the android c compilers: 

```sh
fish_add_path "$HOME/android-ndk-r27c/toolchains/llvm/prebuilt/linux-x86_64/bin"
```

4. Since Termux supports API 24, we set these variables:

```sh
set TARGET_API 24
set CC aarch64-linux-android$TARGET_API-clang
set CXX aarch64-linux-android$TARGET_API-clang++
set AR llvm-ar
set AS llvm-as
set LD ld
set STRIP llvm-strip
set RANLIB llvm-ranlib
set SYSROOT $ANDROID_NDK/toolchains/llvm/prebuilt/linux-x86_64/sysroot
set CFLAGS "-fPIE -fPIC --sysroot=$SYSROOT"
set LDFLAGS "-pie -L$SYSROOT/usr/lib -llog"
```

5. Then we compile:

```sh
$CC -o $BIN_NAME main.c 
```