---
title: Normalized Data Base Structure
author:
  - "E. F. Codd"
doi: "10.1145/1734714.1734716"
url: "https://doi.org/10.1145/1734714.1734716"
pdf_url: "[[Normalized data base structure.pdf]]"
is_oa: false
date created: Sunday, July 20th 2025, 8:31:20 am
date modified: Sunday, July 20th 2025, 6:45:15 pm
---

# Normalized Data Base Structure

There's a difference between the representation of data on disk (storage representation) from its logical representation. As long as an application cannot make a direct reference to data on disk, then its physical representation can be changed without the application being broken by this change.

## Tables and Relations

To make databases useful by casual users, the interface to a DB should be simple and use almost natural language (SQL). The data structure of choice is the table, which are filled with relations. 

The elementary operations on them (like projection, join, filter) are supported.

DB tables have the following properties:

1. Column values have the same type
2. Each column is a number or string (?) (seems pointless)
3. all rows of a table must be distinct (sure)
4. the ordering of rows within a table is irrelevant (not true for performance but to the app programmer)
5. the ordering of columns within a table is irrelevant (not true for performance but to the app programmer, yes)

Each row, since it has a unique set of values in a tuple, can be addressed by its values.

## Additional Data Structure

### Repeating Groups (first Normal form)

Any duplicate information in rows should be factored out into different tables

### Hierarchic Structures (one to many)

one to many relations should be modeled using a foreign key

### Cross Referencing Structure

Foreign key validations should be used to prevent nonsencial cross referencing links in a database (circular graphs)