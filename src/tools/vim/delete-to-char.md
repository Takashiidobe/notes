---
title: delete-to-char
---

to Char

Use `dt${character}` to delete up to but not including \$character.

For example, on this buffer:

    Hello, World!

With the cursor on Hello, `dt,` would delete `Hello`, adding it to the
buffer.

That would leave behind:

    , World!

If you want to delete up to and including `${character}`, use
`df${character}`.

    Hello, World!

Running `dt,` would leave behind:

     World!
