---
title: HTML to Text
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Friday, November 8th 2024, 10:30:57 pm
---

# HTML to Text

If you have python, you can install `html2text` which turns a website to
plain text.

Installation:

```sh
pip install html2text
```

Or if you have `node`, there is a similar `html-to-text`.

```sh
npm install -g html-to-text
```

And then you can curl the website you want and pipe it to either
program.

```sh
curl $website | html-to-text > website.txt
```
