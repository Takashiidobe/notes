---
title: Diffing with Vim
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Tuesday, November 26th 2024, 2:53:20 pm
---

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
