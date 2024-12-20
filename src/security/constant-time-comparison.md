---
title: Constant Time Comparison
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Tuesday, November 12th 2024, 8:38:12 pm
---

# Constant Time Comparison

Using `==` to compare sensitive hashes leaves you vulnerable to timing
attacks. This is because `==` returns `false` as soon as it finds two
characters that don\'t match. An attacker can make many requests with
different values and compare times to figure out how many characters
were correct (the shorter the response, the fewer correct characters).

The solution to this problem is to use a constant-time comparison
algorithm. This ensures that the method will always take the same amount
of time, regardless of how similar the hashes are. In Ruby, you can use
\[`Rack::Utils.secure_compare`\] or
\[`ActiveSupport::SecurityUtils.secure_compare`\].

For more information, check out this excellent \[blog post\].
