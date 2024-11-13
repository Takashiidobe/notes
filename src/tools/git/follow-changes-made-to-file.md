---
title: Follow Changes Made to File
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Tuesday, November 12th 2024, 8:34:58 pm
---

# Follow Changes Made to File

To see all the changes made to one file over time, use the \--follow
flag and the name of a file.

```sh
git log -p --follow index.html
```

Running the command will log all of the patches made to just the file
over the lifetime of the repo.
