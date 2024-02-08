---
title: "pdf.tocgen"
---

[`pdf.tocgen`](https://krasjet.com/voice/pdf.tocgen/) is a set of command-line tools for extracting and generating the table of contents from a PDF file.

It can be installed with pip: `pip install pdf.tocgen`, which installs a set of tools to extract and generate a toc for a pdf that doesn't have one.

First, create a recipe file, which tracks similar elements to make chapters out of:

This creates a rule out of a word in the pdf `_intro-prob.pdf`, which reads page 2 in the document, looking for the word `Introduction`, and writes down the characteristics of the word.

```sh
pdfxmeta --auto 1 --page 2 _intro-prob.pdf "Introduction" >> recipe.toml
```

```toml
[[heading]]
# Introduction
level = 1
greedy = true
font.name = "CMBX12"
font.size = 14.344016075134277
# font.size_tolerance = 1e-5
# font.color = 0x000000
# font.superscript = false
# font.italic = false
# font.serif = true
# font.monospace = false
# font.bold = true
# bbox.left = 96.19835662841797
# bbox.top = 109.06538391113281
# bbox.right = 185.04519653320312
# bbox.bottom = 123.42374420166016
# bbox.tolerance = 1e-5
```

You can then add some more rules, but assuming this is good enough:

You can then generate a table of contents with `pdftocgen` for the document.

```sh
pdftocgen _intro-prob.pdf < recipe.toml
```

```txt
"1 Introduction" 2
"2 Combinatorics" 4
"3 Axioms of Probability" 12
"4 Conditional Probability and Independence" 25
"Interlude: Practice Midterm 1" 40
"5 Discrete Random Variables" 46
"6 Continuous Random Variables" 59
"7 Joint Distributions and Independence" 71
"Interlude: Practice Midterm 2" 82
"8 More on Expectation and Limit Theorems" 88
"Interlude: Practice Final" 105
"9 Convergence in probability" 113
"10 Moment generating functions" 121
"11 Computing probabilities and expectations by conditioning" 128
"Interlude: Practice Midterm 1" 140
"12 Markov Chains: Introduction" 146
"13 Markov Chains: Classification of States" 154
"14 Branching processes" 164
"15 Markov Chains: Limiting Probabilities" 170
"Interlude: Practice Midterm 2" 179
"16 Markov Chains: Reversibility" 185
"17 Three Applications" 191
"18 Poisson Process" 199
"Interlude: Practice Final" 211
```

Verify that it looks correct, then write it to a file called `toc`:

```sh
pdftocgen _intro-prob.pdf < recipe.toml > toc
```

Finally, you can import it to the original pdf file using `pdftocio`, creating a copy called `output.pdf`.

```sh
pdftocio -o output.pdf _intro-prob.pdf < toc
```

And now the pdf should have chapters added to it.
