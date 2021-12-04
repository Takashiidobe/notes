---
title: search-and-replace-with-vim
---

And Replace With Vim

# Search and Replace with Vim

I gave up and looked up how to do it using VIM, I was sure there was a
way.

When VIM is started, you can specify multiple files to open as buffers
from the terminal:

```sh
vim *.html
```

This will open all html files on the current directory as buffers.

- You can list the buffers using `:ls`
- You can add a buffer using `:badd <filename>`
- You can close a buffer using `:bdelete <buffer_number>`

Now you can run commands on all open buffers:

```sh
:bufdo <command>
```

Searching all instances of **foo** and replacing with **bar**:

```sh
:bufdo %s/foo/bar/ge
```

**Notice**: the **e** on the replace command tells vim to ignore errors,
otherwise vim would print an error on each file that doesn\'t have a
match for **foo**

You can now open the buffers (`:buffer <buffer_number>`) and verify that
the text was replaced.

But this command only replaced the text, we need to save the files to
persist changes:

You can either run another **bufdo** with the **update** command to save
the files:

```sh
:bufdo update
```

Or you can pipe it on the first command:

```sh
:bufdo %s/foo/bar/g | update
```

And that\'s it!
