---
title: Multiple Git Identities
date created: Tuesday, November 26th 2024, 2:43:40 pm
date modified: Tuesday, November 26th 2024, 2:52:13 pm
---

# Multiple Git Identities

Source: [^1] 

You can set up multiple git identities by using `includeIf` [^2]. Say if you want to use different git config files based on where the git repo you're working on is:



```ini
[includeIf "gitdir:~/code/**"]
  path = ~/.config/git/personal
[includeIf "gitdir:~/work/**"]
  path = ~/.config/git/work
```

You can also organize them based on the remote url too, so if you want to work on different organizations from the same git forge, you can:

```ini
[includeIf "hasconfig:remote.*.url:git@github.com:orgname/**"]
  path = ~/.config/git/config-gh-org

[includeIf "hasconfig:remote.*.url:git@github.com:*/**"]
  path = ~/.config/git/config-gh

[includeIf "hasconfig:remote.*.url:git@gitlab.com:*/**"]
  path = ~/.config/git/config-gl

[includeIf "hasconfig:remote.*.url:git@git.sr.ht:*/**"]
  path = ~/.config/git/config-srht
```

[^1]: https://www.benji.dog/articles/git-config/
[^2]: https://git-scm.com/docs/git-config#_includes