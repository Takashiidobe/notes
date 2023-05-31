---
title: "Query Planning & Optimization II"
---

# Query Planning & Optimization II

Prev: [query-planning--optimization-i](query-planning--optimization-i.md)
Next: [concurrency-control-theory](concurrency-control-theory.md)

## Cost-Based Query Optimization

The DBMS' optimizer uses an internal cost model to estimate the cost of a query plan. This is a heuristic to choosing which query plan is better, witohut running it.

It can be derived from the following:

- **CPU**: Small cost; tough to estimate
- **Disk**: Number of blocks transferred
- **Memory**: Amount of DRAM used
- **Network**: Number of messages transferred

To calculate the following, the DBMS stores internal statistics about tables, attributes, and indexes in a catalog table. For open source systems, they can be found in `information_schema` or a similar table.

## Statistics

For a relation $R$, the DBMS stores the number of tuples ($N_r$) and the distinct values per attribute ($V (A, R)$).

The selection cardinality ($SC(A, R)$) is the average number of records with a value for an attribute $A$ given $N_R / V(A, R)$.

**Complex Predicates**

- The selectivity of a predicate $P$ is the fraction of tuples that qualify:
    $$sel(A = constant) = SC(P) / V(A,R)$$
- For a range query: $sel(A \ge a) = A_{max} - a / (A_{max} - A_{min}))$
- For negations: $sel(not P) = 1 - sel(P)$.
- The selectivity is the probability that a tuple will satisfy the predicate. Assuming independent predicates, $sel(P_1 \cap P_2) = sel(P1) * sel(P2)$

**Join Estimation**

- Given a join of $R$ and $S$, the estimated size of a join on a non-key attribute ($A$) is:

$$estSize \approx N_R * N_S / max(V(A,R), V(A, S))$$

### Statistics Storage

We don't have to store all values, since it's expensive. We thus want to find a good summary of the data.

**Histograms**:

Histograms work well for uniformly distributed data, but data in real life is not. There are some optimizations, like trying to put data into buckets to reduce the size of histograms. This, however, can lead to inaccuracies.

**Sampling**:

Modern DBMS' use sampling to estimate predicate selectivity. This is simple since you can increase the amount of samples for more accurate data, although it can be skewed by some datasets.

## Search Algorithm

The basic blueprint for a search algorithm is:

1. Bring query from internal form into canonical form
2. Generate multiple execution plans
3. Generate costs for each plan
4. Select plan with smallest cost.

It's important to pick the best access method for each table accessed in the query.

For multiway joins, the number of alternative plans grows rapidly as the number of joined tables increases. For an n-way join, the number of different ways to join the numbers is a Catalan number ($4^n$). This can be cut down with heuristics, like left-deep join trees, which let you pipeline data, and only maintain a single join table in memory.

## Nested Sub-Queries

The DBMS can handle nested sub-queries in a few ways.

1. Rewrite to decorrelate or flatten queries
2. Decompose nested queries and store results in a sub-table.

Prev: [query-planning--optimization-i](query-planning--optimization-i.md)
Next: [concurrency-control-theory](concurrency-control-theory.md)
