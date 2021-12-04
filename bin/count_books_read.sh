#!/usr/bin/env bash

## Counts books read this year if no argument is provided
## Otherwise books read in first argument provided.

if [ $# -eq 0 ]; then
  cat _data/books.csv | grep $(date "+%Y") | wc -l
else
  cat _data/books.csv | grep $1 | wc -l
fi
