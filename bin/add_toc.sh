#!/usr/bin/env bash

# Add table of contents using markdown-toc after ---\n\n.

output="$(markdown-toc --bullets="-" $1 | tail -n +2)"
perl -i -0pe "s/---\n{2}/---\n\n$output\n\n/" $1 
