---
title: movie-festival
---



# Movie Festival

Prev:
[restaurant-customers](restaurant-customers.md)
Next: [sum-of-two-values](sum-of-two-values.md)

In a movie festival n movies will be shown. You know the starting and
ending time of each movie. What is the maximum number of movies you can
watch entirely?

Input

The first input line has an integer n: the number of movies.

After this, there are n lines that describe the movies. Each line has
two integers a and b: the starting and ending times of a movie.

Output

Print one integer: the maximum number of movies.

## Explanation

We'll collect the items into a vector of pairs of {starting_time,
ending_time} and then sort them by their earliest ending_time.

We'll take the first item, since we know it ends first greedily. Then,
for every successive event, if its start_time is greater than or equal
to our end time, we can take that movie, so we'll increment our answer,
and set our current event end to that second value.

Then we'll return our answer.

## Solution

```cpp
{{# include _include/code/algorithms/cses/cpp/sorting-and-searching/movie-festival.cc }}
```

Prev:
[restaurant-customers](restaurant-customers.md)
Next: [sum-of-two-values](sum-of-two-values.md)
