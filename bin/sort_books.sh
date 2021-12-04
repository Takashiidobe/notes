#!/usr/bin/env bash

set -Eeuo pipefail

head -1 _data/books.csv > _data/sorted_books.csv 
tail -n+2 _data/books.csv | sort --field-separator=',' >> _data/sorted_books.csv
mv _data/sorted_books.csv _data/books.csv
