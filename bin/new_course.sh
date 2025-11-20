#!/usr/bin/env bash

set -Eeuo pipefail
trap cleanup SIGINT SIGTERM ERR EXIT

IFS='\"\"'

script_dir=$(cd "$(dirname "${BASH_SOURCE[0]}")" &>/dev/null && pwd -P)

usage() {
  cat <<EOF
Usage: $(basename "${BASH_SOURCE[0]}") [-h]

Generate a new course directory for note taking.

Available options:

-h, --help      Print this help and exit
First argument: The title of the course
Second Argument: A file with newline delimited chapter names.
EOF
  exit
}

cleanup() {
  trap - SIGINT SIGTERM ERR EXIT
}

setup_colors() {
  if [[ -t 2 ]] && [[ -z "${NO_COLOR-}" ]] && [[ "${TERM-}" != "dumb" ]]; then
    NOFORMAT='\033[0m' RED='\033[0;31m' GREEN='\033[0;32m' ORANGE='\033[0;33m' BLUE='\033[0;34m' PURPLE='\033[0;35m' CYAN='\033[0;36m' YELLOW='\033[1;33m'
  else
    NOFORMAT='' RED='' GREEN='' ORANGE='' BLUE='' PURPLE='' CYAN='' YELLOW=''
  fi
}

msg() {
  echo >&2 -e "${1-}"
}

die() {
  local msg=$1
  local code=${2-1} # default exit status 1
  msg "$msg"
  exit "$code"
}

parse_params() {
  # default values of variables set from params
  flag=0
  param=''

  case "${1-}" in
    -h | --help) usage ;;
    -?*) die "Unknown option: $1" ;;
  esac

  args=("$@")

  return 0
}

parse_params "$@"
setup_colors

###### script logic here ########
BOOKS_PATH="src/courses"

# generate an array with the kebab cased files
files=()
mapfile -t files < $2

kebab_cased_dir_name="$(echo $1 | sed 's/[^a-zA-Z0-9 -]//g' | sed 's/[ ]/-/g' | tr '[:upper:]' '[:lower:]')"

corrected_files=()

for key in "${!files[@]}"; do
  corrected_file="$(echo "${files[$key]}" | sed 's/[^a-zA-Z0-9 -]//g' | sed 's/[ ]/-/g' | tr '[:upper:]' '[:lower:]')"
  corrected_files+=($corrected_file)
done

# Create the directory we want
DIR_PATH="$BOOKS_PATH/$kebab_cased_dir_name"
CSV_PATH="_data/courses.csv"

mkdir -p $DIR_PATH

title_template=$(cat << EOF
---
title: "$1"
---

EOF
)

# create the index file we want
echo -e "\"$1\",,,$kebab_cased_dir_name/_$kebab_cased_dir_name,Reading," >> $CSV_PATH
echo -e "- [$1]($kebab_cased_dir_name/_$kebab_cased_dir_name.md)" >> src/courses/_courses.md

len="${#corrected_files[@]}"
pad_width=${#len}
numbered_files=()

for index in "${!corrected_files[@]}"; do
  padded_index=$(printf "%0*d" "$pad_width" $((index + 1)))
  file_slug="${padded_index}-${corrected_files[$index]}"
  numbered_files+=("$file_slug")
done

for index in "${!numbered_files[@]}"; do
  FILE_NAME="$DIR_PATH/${numbered_files[$index]}.md"
  # create the file

  touch $FILE_NAME
file_template=$(cat << EOF
---
title: "${files[$index]}"
---
EOF
)

  echo "$file_template" >> $FILE_NAME
  echo "" >> $FILE_NAME
  echo -e "# ${files[$index]}\n" >> $FILE_NAME
  # Create the title

  if (( index > 0 )); then
    prev_index="$((index - 1))"
    prev_item="${numbered_files[$prev_index]}"
    echo "Prev: [[${prev_item}|${files[$prev_index]}]]" >> $FILE_NAME
  fi

  if (( index < len - 1 )); then
    next_index="$((index + 1))"
    next_item="${numbered_files[$next_index]}"
    echo "Next: [[${next_item}|${files[$next_index]}]]" >> $FILE_NAME
  fi

  echo "" >> $FILE_NAME

  if (( index > 0 )); then
    prev_index="$((index - 1))"
    prev_item="${numbered_files[$prev_index]}"
    echo "Prev: [[${prev_item}|${files[$prev_index]}]]" >> $FILE_NAME
  fi

  if (( index < len - 1 )); then
    next_index="$((index + 1))"
    next_item="${numbered_files[$next_index]}"
    echo "Next: [[${next_item}|${files[$next_index]}]]" >> $FILE_NAME
  fi
done
