---
title: "Course Introduction and the Relational Model"
---

# Course Introduction and the Relational Model

Next: [advanced-sql](advanced-sql.md)

## Databases

A database is an organized collection of related data that models the real world.

A DBMS (database management system manages a database).

## Flat File Strawman

Imagine that we use a CSV to model a database. There's no way to guarantee invariants or integrity, such as no duplicates, or no attributes longer than something, etc.

Issues:

- Data Integrity
    - How do we ensure the artist is the same for each album entry?
    - What if somebody overwrites the album year with an invalid string?
    - How do we store multiple artists on one album?
- Implementation
    - How do you find a particular record?
    - What if we want to create another application that uses the CSV?
    - What if two threads try to write to the same file?
- Durability
    - What happens if the machine crashes mid-update?
    - How do we replicate the database on multiple machines for HA?

## Database Management System

Early databases had a tight coupling between logical and physical layers. So, they were bound to a specific file format, and applications were bound to that as well, which meant if one changed, the other needed to as well.

## Relational Model

The relational model comes from Ted Codd in 1970. It has 3 main points:

1. Store database in simple data structures (relations).
2. Access data through high-level language.
3. Physical storage left up to implementation.

With three concepts:

1. Structure: The definitions of relations and their contents.
2. Integrity: The database contents should satisfy constraints.
3. Manipulation: how to access and modify the database contents.

A relation is an unordered set that contains attributes. Since they are unordered, the database can store them anyway it wants, allowing for optimization.

A tuple is a set of attribute values (also known as its domain) in the relation. Every attribute is nullable.

A relation with **n** attributes is called an **n-ary** relation.

A relation's primary key uniquely identifies a single tuple.

A foreign key specifies that an attribute from one relation has to map to a tuple in another relation.

## Data Manipulation Languages (DMLs)

- Procedural: The language specifies the high-level strategy to find the desired result.
- Non-procedural: The query specifies only what data is wanted, and not how to find it.

## Relational Algebra

Relational algebra is a set of fundamental operations to retrieve and manipulate tuples in a relation. Each operator takes in one or more relations as inputs, and outputs a new relation. These can be changed for more complex operations.

**Select**:
Select takes a relation and outputs a subset of tuples that satisfies the predicate.

Syntax: $\sigma \text{ predicate}(R)$.

**Projection**:
Projection takes a relation and outputs a relation with tuples that contain only the specified attributes. You can rearrange the ordering of the attributes and manipulate the values.

Syntax: $\pi$ $A1, A2, ..., An(R)$.

**Union**:
Union takes in two relations and outputs a relation that contains all tuples that appear in at least one of the input relations.

Syntax: $(R \cup S)$.

**Intersection**:
Intersection takes in two relations and outputs a relation that contains all tuples that appear in both of the input relations.

Syntax: $(R \cap S)$

**Difference**:
Difference takes in two relations and outputs a relation that contains all tuples that appear in the first relation, but not the second relation.

Syntax: $(R - S)$

**Product**:
Product takes in two relations and outputs a relation that contains all possible combinations for tuples from the input relations.

Syntax: $(R \times S)$

**Join**:
Join takes in two relations and outputs a relation that contains all the tuples that are a combination of two tuples for each attribute that the two relations share, the value for that attribute of both tuples is the same.

Syntax: $(R \bowtie S)$

Next: [advanced-sql](advanced-sql.md)
