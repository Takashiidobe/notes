#!/usr/bin/env bash

set -Eeuo pipefail

head -1 _data/music.csv > _data/sorted_music.csv 
tail -n+2 _data/music.csv | sort --field-separator=',' -k2,3 >> _data/sorted_music.csv
mv _data/sorted_music.csv _data/music.csv
