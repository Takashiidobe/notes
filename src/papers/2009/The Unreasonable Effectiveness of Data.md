---
title: The Unreasonable Effectiveness of Data
date created: Wednesday, October 4th 2023, 11:09:05 am
date modified: Saturday, December 7th 2024, 8:34:33 pm
pdf_url: "[[The Unreasonable Effectiveness of Data.pdf]]"
---

# The Unreasonable Effectiveness of Data

This paper, written in 2009, takes inspiration from "The Unreasonable effectiveness of Mathematics in the Natural Sciences" and tries to explain why data has been so useful at transforming many problems that were previously seen to be impenetrable.

This paper from Google AI outlines why large datasets are so beneficial to solving AI related problems, due to the problems being so vague. An informal grammar of the English language is 1700 pages.

For example, 20 years ago, the biggest corpus for training on was 1 million words, the Brown Corpus. In 2006, google released the n-grams dataset with a trillion words,in n-grams up to 5 word sequences. Of course, this dataset was not manually tagged, but because it was a million times larger, it allowed natural language machine learning models do better on much more complicated tasks.

The first lesson of using the web to train models on complicated problems is to use available large-scale data rather than hoping for annotated data. Thus the first maxim, simple models and lots of data trump elaborate models on less data.

For many models, there is a threshold of sufficient data: for the problem of scene completion, where removing an unwanted object from a photo and then filling it in, with a set of thousands of photos, the results were poor. However, when they accumulated millions of photos, the algorithm performed very well. Even though the number of possible 2MB photos is $256 ^ 2,000,000$, there are only really a finite number of distinctions. At around 1 billion examples, most problems don't become as data constrained.

Since natural language is inherently complex, a simple approach just doesn't work.

There are three orthogonal problems:

1. Choosing a representation language
2. Encoding a model in that language
3. Performing inference on that model

As well, you can't throw away outliers because they tend to be really useful for explaining rare but important concepts.

Tl;dr: Choose a representation that can use unsupervised learning on unlabeled data, which is so much more plentiful than labeled data.
