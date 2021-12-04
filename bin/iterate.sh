#!/usr/bin/env zsh

shopt -s globstar

for f in _src/**/*.md.html.html; do
  pandoc $f -o ${f%%.*}.md
done
