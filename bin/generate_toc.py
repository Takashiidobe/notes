#!/usr/bin/env python3

import os
import re
import subprocess
from Levenshtein import distance

summary_str = r"""# Table of Contents
- [Table of Contents](./SUMMARY.md)
"""

replacements = {}

# Handles SUMMARY.md generation
for root, dirs, files in sorted(os.walk("src")):
    for name in sorted(files, key=lambda d: d.replace("_", "`")):
        rel_dir = os.path.relpath(root, ".")
        file_name = os.path.join(rel_dir, name)
        if file_name.lower().endswith(('readme.md', 'summary.md', 'index.md')):
            continue
        if file_name.lower().endswith(('.md')):
            dir_path = os.path.dirname(os.path.realpath(file_name))
            curr_dir = dir_path.split('/')[-1]
            basename = os.path.basename(file_name)
            close = distance(curr_dir, basename.replace(' ', '').replace('_', '').split('.')[0]) == 0
            depth = file_name.count('/')
            if close and basename.startswith('_'):
                depth -= 1
            link_title = file_name[:-3].split('/')[-1].replace('-', ' ').replace('_', ' ')
            summary_str += f"{' ' * depth * 2}- [{link_title.title()}](./{file_name[4:]})\n"

with open('src/SUMMARY.md', 'w+') as f:
    f.write(summary_str)

subprocess.run(["sed", "-i", "-r", "s/\[ /\[/g", "src/SUMMARY.md"])
