#!/usr/bin/env bash

CLEAR='\033[0m'
RED='\033[0;31m'

function usage() {
  if [ -n "$1" ]; then
    echo -e "${RED}👉 $1${CLEAR}\n";
  fi
  echo "Usage: $0 [-a artist] [-r record]"
  echo "  -a, --artist             the artist(s) who made the record"
  echo "  -r, --record             the record title"
  echo ""
  echo "Example: $0 -a radiohead -r 'ok computer'"
  exit 1
}

# parse params
while [[ "$#" > 0 ]]; do case $1 in
  -a|--artist) ARTIST="$2"; shift;shift;;
  -r|--record) RECORD="$2";shift;shift;;
  *) usage "Unknown parameter passed: $1"; shift; shift;;
esac; done

# verify params
if [ -z "$ARTIST" ]; then usage "Artist is not set"; fi;
if [ -z "$RECORD" ]; then usage "Record is not set."; fi;

URL=$(album-art $ARTIST --album $RECORD --size 'medium')

RECORD_FILE_NAME=${RECORD// /-}
IMAGE_LOCATION="../../assets/covers/$RECORD_FILE_NAME.jpg"
IMAGE_LINK="/assets/covers/$RECORD_FILE_NAME.jpg"
TITLE_CASED_ALBUM_TITLE=$(echo $RECORD | sed 's/.*/\L&/; s/[a-z]*/\u&/g')

echo "Downloading file to $IMAGE_LOCATION" 
curl $URL -o $IMAGE_LOCATION 

echo "![$TITLE_CASED_ALBUM_TITLE]($IMAGE_LINK)" >> _music.md