---
title: Aerc
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Tuesday, November 12th 2024, 8:40:32 pm
---

# Aerc

Aerc is an email client that works in the terminal.

Install it with `brew install aerc`.

The config I use is below:

```toml
[viewer]
pager=/usr/local/bin/bat
alternatives=text/html,text/plain

[filters]
subject,~^\[PATCH=awk -f @SHAREDIR@/filters/hldiff
text/html=/usr/local/bin/w3m -T text/html -o display_link_number=1
text/*=awk -f /usr/local/share/aerc/filters/plaintext
```

This lets me access e-mail in the terminal.
