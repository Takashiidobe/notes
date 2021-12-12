---
title: Id3tool
---

# Id3tool

## Context

`Id3tool` is an mp3 tagger.

## Installation

`brew install id3tool`

## Usage

Run `id3tool $file` to get the tagged information for the file:

```sh
$ id3tool illmatic\ -\ 01\ \ -\ Nas\ -\ The\ Genesis\ \[Y6ElJoP_2S8\].mp3
Filename: illmatic - 01  - Nas - The Genesis [Y6ElJoP_2S8].mp3
Song Title:	The Genesis
Artist:		Nas
Album:		Illmatic
Track:		1
Year:		1994
```

You can tag it like so:

```sh
id3tool "$f" -y "$year" -a "$album" -r "$artist" -t "$track_name" -c "$track_number"
```
