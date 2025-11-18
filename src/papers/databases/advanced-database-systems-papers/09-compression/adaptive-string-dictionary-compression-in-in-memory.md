---
title: "Adaptive String Dictionary Compression In In Memory"
pdf_url: "[[adaptive-string-dictionary-compression-in-in-memory.pdf]]"
---
## Notes

This paper discusses dictionary compression of string columns in in-memory data stores. 
They note that most columns are strings, and that many columns have only a few values, but some have large dictionaries.

They list out a few schemes:

- Uncompressed
- Bit compression
- Hu-Tucker (order-preserving Huffman)
- N-gram compression.
- Re-pair

All of these do well depending on the data.

For each scheme, they lay out a prediction model for the variant, and then build out a compression manager, which gets statistics on the space and time for compression of the column based on the set size, which tunes itself to trade time for space.

If memory pressure is high, favor more compression
If memory pressure is low, favor less compression

They plot out a curve where variants would fit for this column and then pick the one that takes the least time.
