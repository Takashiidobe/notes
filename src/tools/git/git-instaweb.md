---
title: git-instaweb
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Tuesday, November 12th 2024, 8:34:52 pm
---

If you\'d like to see a small git frontend, you can do this in the root
of a git repository:

```sh
git instaweb --httpd=webrick
```

This will start a CGI server that has some metadata about your git repo.
