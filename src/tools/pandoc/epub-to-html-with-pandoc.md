---
title: EPUB to HTML with Pandoc
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Tuesday, November 26th 2024, 2:53:38 pm
---

# EPUB to HTML with Pandoc

To turn an epub to HTML with Pandoc, you'll need to extract the html
file with pandoc.

This command extracts the files into the base directory. As well, it
uses the new.min.css files for the styles in the epub.

This applies the CSS styles to the epub and extracts the images into the
base directory.

```sh
pandoc -s --extract-media=. $INPUT.epub -o $OUTPUT.html -c https://cdn.jsdelivr.net/npm/@exampledev/new.css@1.1.2/new.min.css
```
