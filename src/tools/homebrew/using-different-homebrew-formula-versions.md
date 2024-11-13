---
title: Using Different Homebrew Formula Versions
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Tuesday, November 12th 2024, 8:35:26 pm
---

# Using Different Homebrew Formula Versions

Today, I was trying to run the executable from a gem and got the
following error:

    This installation of RMagick was configured with ImageMagick 6.8.9 but
    ImageMagick 6.9.0-3 is in use. (RuntimeError)

My first instinct was to uninstall ImageMagick 6.9.0 and then install
6.8.9 with Homebrew. Through googling, I learned that Homebrew saves
older formula versions. You can see which versions you have like this
(notice the asterisk next to the version in use):

```sh
% brew info imagemagick
imagemagick: stable 6.9.0-3 (bottled), HEAD
http://www.imagemagick.org
/usr/local/Cellar/imagemagick/6.8.8-9 (1429 files, 21M)
/usr/local/Cellar/imagemagick/6.8.9-1 (1432 files, 22M)
/usr/local/Cellar/imagemagick/6.9.0-3 (1440 files, 22M) *
```

Since I already had 6.8.9 installed, I could set it as my active version
like so:

```sh
% brew switch imagemagick 6.8.9-9
```

Problem: solved.
