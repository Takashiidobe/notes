---
title: gooey
---

# Gooey

Gooey is a python package that turns your CLI apps into GUIs with
python.

## Installation

Install Gooey with pip.

```sh
pip3 install gooey
```

## Example

```py
from gooey import Gooey, GooeyParser
from os import system


@Gooey
def main():
    parser = GooeyParser()
    parser.add_argument('url')
    args = parser.parse_args()
    system(f'youtube-dl --extract-audio --audio-format mp3 "{args.url}"')

main()
```
