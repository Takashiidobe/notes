---
title: to-pdf
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Tuesday, November 26th 2024, 2:53:40 pm
---

To convert to pdf, I use the eisvogel theme: [here](https://github.com/Wandmalfarbe/pandoc-latex-template.md).
You'll need to move the eisvogel.tex file to your `$HOME/.pandoc/templates` directory. You'll also need to install a list of packages with tlmgr.

```
sudo tlmgr install adjustbox babel-german background bidi collectbox csquotes everypage filehook footmisc footnotebackref framed fvextra letltxmacro ly1 mdframed mweights needspace pagecolor sourcecodepro sourcesanspro titling ucharcat ulem unicode-math upquote xecjk xurl zref
```

Once you have all these, just build:

```sh
pandoc $INPUT_FILE -o $OUTPUT_FILE --template eisvogel --pdf-engine=xelatex
```
