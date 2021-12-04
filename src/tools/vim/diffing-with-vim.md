---
title: diffing-with-vim
---

With Vim

# Diffing with Vim

Vim comes with its own diff viewer. It can be launched from the
command-line with:

```sh
vim -d $file1 $file2
# or
vimdiff $file1 $file2
```

You can also diff within vim by opening two files in splits and running
`:diffthis`.

More info at `:help vimdiff`
