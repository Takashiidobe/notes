---
title: "Query Planning & Optimization I"
---

# Query Planning & Optimization I

Prev: [query-execution-ii](query-execution-ii.md)
Next: [query-planning--optimization-ii](query-planning--optimization-ii.md)

## Overview

SQL is declarative, so the DBMS needs to generate the "best" plan for a given query.

Optimization is an NP-hard problem, so there's no computationally cheap way to solve the optimization problem.

Thus, Heuristics and Cost-based search are some guiding principles to optimize queries.

## Rule-based Query Optimization

The DBMS can rewrite an expression with a cheaper one if they generate the same set of tuples. Some examples:

- **Predicate Push-down**: Perform predicate filtering before join to reduce the size of a join
- **Projections Push-down**: Perform projections earlier to create smaller tuples and reduce intermediate results.
- **Expression Simplification**: Exploit transitive properties to rewrite predicate expressions into a simpler form.

Prev: [query-execution-ii](query-execution-ii.md)
Next: [query-planning--optimization-ii](query-planning--optimization-ii.md)
