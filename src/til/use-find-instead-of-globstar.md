---
title: Use Find instead of Globstar
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Saturday, December 7th 2024, 8:58:13 pm
---

# Use Find instead of Globstar

Globstar allows you to recursively search through a directory:

That would look something like this:

```sh
shopt -s globstar

for f in $(ls **/*.md); do
  echo $f
done
```

Globstar, however, requires bash 4.X, which mac doesn\'t have (it
defaults to 3.X).

Instead, we can find all \".md\" files in the current directory
recursively using find.

```sh
for f in $(find . -name ; do
  echo $f
done
```

No more bash 4.X+ required!
