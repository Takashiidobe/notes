---
title: delta
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Saturday, November 9th 2024, 7:27:44 am
---

If you want cleaner diffs for git, install delta with
`brew install delta`. [Delta](https://github.com/dandavison/delta).

Here\'s an example .gitconfig file that allows github style diffs.

    [core]
        pager = delta

    [delta]
        side-by-side = true
        plus-style = "syntax #012800"
        minus-style = "syntax #340001"
        syntax-theme = Gruvbox Dark
        navigate = true

    [delta "unobtrusive-line-numbers"]
        line-numbers = true
        line-numbers-minus-style = "#444444"
        line-numbers-zero-style = "#444444"
        line-numbers-plus-style = "#444444"
        line-numbers-left-format = "{nm:>4}┊"
        line-numbers-right-format = "{np:>4}│"
        line-numbers-left-style = blue
        line-numbers-right-style = blue

    [delta "decorations"]
        commit-decoration-style = bold yellow box ul
        file-style = bold yellow ul
        file-decoration-style = none
        hunk-header-decoration-style = yellow box

    [interactive]
        diffFilter = delta --color-only
