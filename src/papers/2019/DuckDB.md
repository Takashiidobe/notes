---
title: DuckDB
author:
  - "Hannes Mühleisen"
  - "Mark Raasveldt"
doi: "10.1145/3299869.3320212"
url: "https://doi.org/10.1145/3299869.3320212"
pdf_url: "[[DuckDB.pdf]]"
is_oa: true
date created: Sunday, July 20th 2025, 8:20:23 am
date modified: Sunday, July 20th 2025, 12:35:53 pm
---

# DuckDB

DuckDB is an embeddable SQL db like SQLite that is meant for analytic (OLAP) workloads, compared to SQLite, which is for transactional (OLTP) workloads.

## Introduction

SQLite is deployed on over a trillion devices and is fast on transactional workloads, using B-Trees and a row based execution engine. 

A very popular workload these days is for data analysis (R, python) as well as embeddable devices for edge computing.

DuckDB follows MonetDB, where the authors found these concerns:

1. High Efficiency for OLAP without sacrificing OLTP
2. Efficient transfer of tables to and from the DB
3. Stability (no crashing, + aborting queries)
4. Practical embeddability -- no requiring outside libraries or signals

## Design and Implementation

DuckDB follows the textbook implementation of a database:

- Parser
- Logical planner
- Optimizer
- Physical Planner
- Execution Engine

- The parser is derived from Postgres' SQL parser, but stripped down for DuckDB's use. The parse tree from the parsing step is turned in C++ classes.
- The logical planner has two parts, the binder and plan generator. The binder resolves expressions referring to schema objects, and then the plan generator turns the AST into logical query operators like scan, filter, project.
- The optimizer performs join order optimization with dynamic programming, with fallbacks to greedy in case of complicated algorithms. As well, there are simplification rules like common subexpression elimination and constant folding.
- The physical planner turns this into an actual plan, which selects indexes, and uses join algorithms like hash or merge joins, etc.
- The execution engine is vectorized and runs a vectorized volcano model, where queries pull chunks recursively from child nodes.
- ACID compliance is MVCC, which uses an undo buffer for concurrent transactions.
- The storage layout is datablocks, which horizontally partitions columns into compressed blocks, with min/max indexes for each column to note if they are relevant to certain queries.