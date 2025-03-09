#!/usr/bin/env python3

from os import walk
from os.path import join
from pathlib import Path

visited = set()


def gen_index_file(file_path, sub_dirs, sub_files):
    index_file_path = join(file_path, "index.md")
    if index_file_path in visited:
        return
    visited.add(index_file_path)
    if Path(index_file_path).exists():
        with open(join(file_path, "index.md"), "r+") as f:
            parse_tags(f)
            write_contents(f, sub_dirs, sub_files)
    else:
        with open(join(file_path, "index.md"), "w+") as f:
            write_contents(f, sub_dirs, sub_files)


def parse_tags(f):
    file_content = f.read()
    split_up = file_content.split("---")
    contents = []
    if len(split_up) == 3:
        contents.append("---")
        contents.append(split_up[1])
        contents.append("---\n\n")
        contents.append(f"# {file_path.split('/')[-1].title().replace('-', ' ')}\n\n")
    f.seek(0)
    f.truncate()
    f.writelines(contents)


def write_contents(f, sub_dirs, sub_files):
    contents = []
    for subdir in sub_dirs:
        joined_path = join(subdir, "index.md")
        title = subdir.replace("-", " ").title()
        contents.append(f"- [{title}]({joined_path})\n")
    for sub_file in sub_files:
        joined_path = join(sub_file)
        title = sub_file.replace("-", " ").removesuffix(".md").title()
        contents.append(f"- [{title}]({joined_path})\n")
    contents.sort()
    title = f.name.split("/")[-2].title().replace("-", " ")
    contents.insert(0, f"# {title}\n\n")
    contents = [l for l in contents if l != "- [Index](index.md)\n"]
    f.writelines(contents)


for file_path, sub_dirs, sub_files in walk("src"):
    if ".obsidian" in file_path:
        continue
    for sub_dir in sub_dirs:
        gen_index_file(file_path, sub_dirs, sub_files)
    for sub_file in sub_files:
        gen_index_file(file_path, sub_dirs, sub_files)
