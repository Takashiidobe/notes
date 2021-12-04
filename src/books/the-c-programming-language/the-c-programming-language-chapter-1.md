---
title: the-c-programming-language-chapter-1
---

C Programming Language Chapter 1

# Chapter 1

## Exercise 1-1

> Run the `hello world` program on your system. Experiment with leaving
> out parts of the program, to see what error messages you get.

```c
{{# include _include/code/programming-languages/c/the-c-programming-language/chapter-1/1-1/main.c }}
```

## Exercise 1-2

> Experiment to find out what happens when `prints`'s argument string
> contains c where c is some character not listed above.

Some escape characters include n for newline, t for tab, ' for
single quote, " for double quote,  for literal backslash, r for
carriage return, f for form feed, b for backspace.

```c
{{# include _include/code/programming-languages/c/the-c-programming-language/chapter-1/1-2/main.c }}
```

## Exercise 1-3

> Add a `printf` statement before the while loop.

```c
{{# include _include/code/programming-languages/c/the-c-programming-language/chapter-1/1-3/main.c }}
```

## Exercise 1-4

> Write a program to print the corresponding Celcius to Fahrenheit
> table.

```c
{{# include _include/code/programming-languages/c/the-c-programming-language/chapter-1/1-4/main.c }}
```

## Exercise 1-5

> Modify the temperature conversion program to print the table in
> reverse order, that is, from 300 degrees to 0.

```c
{{# include _include/code/programming-languages/c/the-c-programming-language/chapter-1/1-5/main.c }}
```

## Exercise 1-6

> Verify that the expression getchar() != EOF is 0 or 1.

EOF is -1 when cast to an int, and the expression != casts to either 0
(false) or 1 (true). Therefore, the expression has to be 0 or 1.

```c
{{# include _include/code/programming-languages/c/the-c-programming-language/chapter-1/1-6/main.c }}
```

## Exercise 1-7

> Write a program to print the value of `EOF`.

```c
{{# include _include/code/programming-languages/c/the-c-programming-language/chapter-1/1-7/main.c }}
```

## Exercise 1-8

> Write a program to count blanks, tabs, and newlines.

```c
{{# include _include/code/programming-languages/c/the-c-programming-language/chapter-1/1-8/main.c }}
```

## Exercise 1-9

> Write a program to copy its input to its output, replacing each string
> of one or more blanks by a single blank.

```c
{{# include _include/code/programming-languages/c/the-c-programming-language/chapter-1/1-9/main.c }}
```

## Exercise 1-10

> Write a program to copy its input to its output, replacing each tab by
> t, each backspace by b, and each backslash by . This makes tabs
> and backspaces visible in an unambiguous way.

```c
{{# include _include/code/programming-languages/c/the-c-programming-language/chapter-1/1-10/main.c }}
```

## Exercise 1-11

> How would you test the word count program? What kinds of input are
> most likely to uncover bugs if they are any?

I would test the word count program by adding lots of corpuses at it. I
see one bug, where it doesn't split on punctuation other than newline
or tab.

## Exercise 1-12

> Write a program that prints its input one word per line.

```c
{{# include _include/code/programming-languages/c/the-c-programming-language/chapter-1/1-12/main.c }}
```

## Exercise 1-13

> Write a program to print a histogram of the lengths of words in its
> input. It is easy to draw the histogram with the bars horizontal; a
> vertical orientation is more challenging.

```c
{{# include _include/code/programming-languages/c/the-c-programming-language/chapter-1/1-13/main.c }}
```

## Exercise 1-14

> Write a program to print a histogram of the frequencies of different
> characters in its input.

```c
{{# include _include/code/programming-languages/c/the-c-programming-language/chapter-1/1-14/main.c }}
```

## Exercise 1-15

> Rewrite the temperature conversion program of Section 1.2 to use a
> function for conversion.

```c
{{# include _include/code/programming-languages/c/the-c-programming-language/chapter-1/1-15/main.c }}
```

## Exercise 1-16

> Revise the main routine of the longest-line program so it will
> correctly print the length of arbitrarily long input lines, and as
> much as possible of the text.

```c
{{# include _include/code/programming-languages/c/the-c-programming-language/chapter-1/1-16/main.c }}
```

## Exercise 1-17

> Write a program to print all input lines that are longer than 80
> characters.

```c
{{# include _include/code/programming-languages/c/the-c-programming-language/chapter-1/1-17/main.c }}
```

## Exercise 1-18

> Write a program to remove all trailing blanks and tabs from each line
> of input, and to delete entirely blank lines.

```c
{{# include _include/code/programming-languages/c/the-c-programming-language/chapter-1/1-18/main.c }}
```

## Exercise 1-19

> Write a function reverse(s) that reverses the character string s. Use
> it to write a program that reverses its input a line at a time.

```c
{{# include _include/code/programming-languages/c/the-c-programming-language/chapter-1/1-19/main.c }}
```

## Exercise 1-20

> Write a program detab that replaces tabs in the input with the proper
> number of blanks to space to the next tab stop. Assume a fixed set of
> tab stops, say every n columns. Should n be a variable or a symbolic
> parameter?

```c
{{# include _include/code/programming-languages/c/the-c-programming-language/chapter-1/1-20/main.c }}
```

## Exercise 1-21

> Write a program entab that replaces strings of blanks with the minimum
> number of tabs and blanks to achieve the same spacing. Use the same
> stops as for detab . When either a tab or a single blank would suffice
> to reach a tab stop, which should be given preference?

```c
{{# include _include/code/programming-languages/c/the-c-programming-language/chapter-1/1-21/main.c }}
```

## Exercise 1-22

> Write a program to "fold" long input lines into two or more shorter
> lines after the last non-blank character that occurs before the n -th
> column of input. Make sure your program does something intelligent
> with very long lines, and if there are no blanks or tabs before the
> specified column.

```c
{{# include _include/code/programming-languages/c/the-c-programming-language/chapter-1/1-22/main.c }}
```

## Exercise 1-23

> Write a program to remove all comments from a C program. Don't forget
> to handle quoted strings and character constants properly. C comments
> do not nest.

```c
{{# include _include/code/programming-languages/c/the-c-programming-language/chapter-1/1-23/main.c }}
```

## Exercise 1-24

> Write a program to check a C program for rudimentary syntax errors
> like unbalanced parentheses, brackets and braces. Don't forget about
> quotes, both single and double, escape sequences, and comments. (This
> program is hard if you do it in full generality.)

```c
{{# include _include/code/programming-languages/c/the-c-programming-language/chapter-1/1-24/main.c }}
```
