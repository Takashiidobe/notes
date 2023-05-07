---
title: "Query Execution I"
---

# Query Execution I

Prev: [joins-algorithms](joins-algorithms.md)
Next: [query-execution-ii](query-execution-ii.md)

## Query Plan

The DBMS converts an SQL statement into a query plan. This is an AST. The DBMS is responsible for iterating through the query and running it. It can optimize it as well.

## Processing Models

A processing model defines how the system executes a query plan. Each model has different tradeoffs.

**Iterator Model**
The most common model for row-based DBMSes. Each operator implements a next function that:
- Either returns a single tuple or a null tuple (if there are no more tuples).
- Implements a loop that calls next on its children to retrieve their tuples and process them as well (calling next on a parent calls next on their children).
Some operators block until children emit their tuples (like joins, subqueries, order by). These are called pipeline breakers.

Output control (like LIMIT and OFFSET) work well with this approach, because an operator can stop invoking next after it has received enough tuples.

**Materialization Model**
Each operator processes its input all at once and emits its output all at once.

Each query plan implements an output function:
- The operator processes all tuples from all children at once.
- The return result is all the tuples the operator will ever emit. Thus, the DBMS never needs to call it once it has called it before.
This can be good for OLTP workloads, since data is normally small.

**Vectorization Model**
- Like the iterator model, but the operator emits a vector of tuples instead of just one.

## Access Methods

An access method is the way the DBMS accesses the data stored in a table.

**Sequential Scan**
For each page in the table, iterate over each page. For each page, iterate over all tuples, and evaluate the predicate on tuples.

Optimizations:

- **Prefetching**: Fetches next pages in advance
- **Parallelization**: Execute the scan on multiple threads
- **Buffer Pool Bypass**: Avoiding cache trashing by not adding pages to the buffer pool
- **Zone Map**: Pre-compute aggregations for each tuple attribute in a page. The DBMS can check whether it needs to access a page by checking its Zone Map first.
- **Late Materialization**: Each operator passes the minimum amount of information required.
- **Heap Clustering**: Tuples are stored in the heap pages using an order specified by a clustering index.

**Index Scan**

The DBMS picks an index or indexes to find the tuples the query needs.

When using multiple indexes, the DBMS does the search on each index and generates the matching record ids. It can do this with bitmaps, hash tables, or bloom tables to filter the record set.

## Expression Evaluation

The DBMS represents a query plan as a tree. Inside of the operators is an AST.

The nodes in the tree are different expression types:

- Comparisons (=, \<, \>, !=)
- Conjuction (AND, Disjunction (OR)
- Arithmetic Operators (+, -, *, / %)
- Constant and Parameter Values
- Tuple Attribute References

To evaluate the tree, the DBMS walks through the tree, fetching tuples and evaluating.

Prev: [joins-algorithms](joins-algorithms.md)
Next: [query-execution-ii](query-execution-ii.md)
