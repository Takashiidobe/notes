#!/usr/bin/env python3
import pandas as pd

col_list = ["title", "notes"]

df = pd.read_csv("./_data/books.csv", usecols=col_list)

s = """
---
title: Books
---

"""

for x, y in zip(df["title"], df["notes"]):
    s += f"- [{x}]({y}.md)\n"

with open("src/books/_books.md", "w+") as f:
    f.write(s)
