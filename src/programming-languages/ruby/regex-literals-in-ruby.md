---
title: regex-literals-in-ruby
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Friday, November 8th 2024, 10:27:01 pm
---

Regexes literals in ruby don\'t require escaping for slashes.

Instead of:

```rb
/http:\/\/sub\.domain\.com\/path/
```

You can use this:

```rb
%r{http://sub\.domain\.com/path}
```
