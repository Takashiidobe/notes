---
title: regex-literals-in-ruby
---

Literals In Ruby

Regexes literals in ruby don\'t require escaping for slashes.

Instead of:

```rb
/http:\/\/sub\.domain\.com\/path/
```

You can use this:

```rb
%r{http://sub\.domain\.com/path}
```
