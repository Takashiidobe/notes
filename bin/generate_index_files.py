#!/usr/bin/env python3

from os import walk
from os.path import join
from pathlib import Path


def gen_index_file(file_path, sub_dirs, sub_files):
    index_file_path = join(file_path, "index.md")
    if Path(index_file_path).exists():
        with open(join(file_path, "index.md"), "r+") as f:
            file_content = f.read()
            split_up = file_content.split("---")
            if len(split_up) == 3:
                contents = []
                f.seek(0)
                f.write("---")
                f.write(split_up[1])
                f.write("---\n\n")
                f.write(f"# {file_path.split('/')[-1].title().replace('-', ' ')}\n\n")
                for subdir in sub_dirs:
                    joined_path = join(subdir, "index.md")
                    title = subdir.replace("-", " ").title()
                    contents.append(f"- [{title}]({joined_path})\n")
                for sub_file in sub_files:
                    joined_path = join(sub_file)
                    title = sub_file.replace("-", " ").removesuffix(".md").title()
                    contents.append(f"- [{title}]({joined_path})\n")
                contents.sort()
                f.writelines(contents)
                f.truncate()
    else:
        with open(join(file_path, "index.md"), "w+") as f:
            f.write(f"# {file_path.split('/')[-1].title().replace('-', ' ')}\n\n")
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
            f.writelines(contents)


for file_path, sub_dirs, sub_files in walk("src"):
    if ".obsidian" in file_path:
        continue
    for sub_dir in sub_dirs:
        gen_index_file(file_path, sub_dirs, sub_files)
    for sub_file in sub_files:
        gen_index_file(file_path, sub_dirs, sub_files)
