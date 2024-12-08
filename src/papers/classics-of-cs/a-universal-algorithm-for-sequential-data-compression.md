---
title: A Universal Algorithm for Sequential Data Compression
date created: Wednesday, October 4th 2023, 10:20:28 am
date modified: Saturday, December 7th 2024, 8:35:41 pm
---

# A Universal Algorithm for Sequential Data Compression

This paper outlines LZ77 and LZ78 compression, which is the basis of many compression algorithms, such as GIF, DEFLATE, PNG and ZIP.

LZ77 achieves compression by replacing repeated occurrences of data with references to a single copy of that data existing earlier in the uncompressed data stream. A match has a pair of numbers, with a length - distance pair. The psuedo-code would look like this:

```
while input is not empty do
    match := longest repeated occurrence of input that begins in window

    if match exists then
        d := distance to start of match
        l := length of match
        c := char following match in input
    else
        d := 0
        l := 0
        c := first char of input
    end if

    output (d, l, c)

    discard l + 1 chars from front of window
    s := pop l + 1 chars from front of input
    append s to back of window
repeat
```
