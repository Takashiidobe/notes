---
title: chawan
date created: Thursday, December 26th 2024, 11:12:18 am
date modified: Thursday, December 26th 2024, 11:36:18 am
---

Chawan is a TUI web browser, which comes with support for man pages (mancha):

Install it here: https://git.sr.ht/~bptato/chawan

You'll need a nim compiler.

I use `mancha` as my normal man command.

My config file is at ~/.config/chawan/config.toml, and has this.

```toml
[page]
'n' = 'cmd.pager.nextBuffer'
'b' = 'cmd.pager.prevBuffer'
```