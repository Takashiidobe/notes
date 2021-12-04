---
title: data-models-and-query-languages
---

Models and Query Languages"

# Data Models and Query Languages

Prev:
[reliable-scalable-and-maintainable-applications](reliable-scalable-and-maintainable-applications.md)
Next:
[storage-and-retrieval](storage-and-retrieval.md)

Data Models are APIs built on top of APIs. Bad data models are awkward
to use.

## The Relational Vs. Document Model

Relational DBs have their roots in the 70s with Codd.

NoSQL became popular in the 2010s, driven by these factors:

- A need for greater scalability than relational databases can easily
  achieve, including very large datasets or very high write throughput
- A widespread preference for free and open source software over
  commercial database products
- Specialized query operations that are not well supported by the
  relational model
- Frustration with the restrictiveness of relational schemas, and a
  desire for a more dynamic and expressive data model

### The Object-Relational Mismatch

Since we code primarily in object oriented languages, there's a
mismatch between SQL and how ORMs are used.

Compare a data model that uses JSON vs one that uses normalized tables.
The JSON data model has better cache locality, as the Relational data
model requires lots of joins (which take time).

You should try to store duplicated data as ids, and have a lookup table
mapping from id -> value. Instead of saying "industry": "Software",
you should instead say "industry_id": 131, where 131 corresponds to
"Software". This reduces code duplication and allows for fast changes
for all callers if the name of the item changes.

## Many-to-One and Many-to-Many Relationships

Joins are weakly supported in NoSQL databases, and shift a lot of the
burden to the application developer instead of the database developer.

## Relational Versus Document Databases Today

If your data can be represented with `one-to-many` relationships, a
document model will suffice.

For data with `many-to-many` relationships, relational databases may aid
in data modeling.

If you prefer a schemaless setup (i.e. migrations are cumbersome and
your data changes fast, you may prefer a NoSQL setup, since adding keys
to an object is backwards compatible).

## Query Languages for Data

In imperative code, in order to get data, you might write something like
this:

```py
def get_sharks(animals):
  return [animal for animal in animals if animal.family == "Sharks"]
```

In SQL, you write this declaratively:

```sql
SELECT * from animals where family = 'Sharks';
```

### MapReduce Querying

In Mapreduce, a parallel querying framework, you might write these
functions:

```js
db.observations.mapReduce(
  function map() {
    var age = this.age;
    emit(age); // get the age of each shark from the document
  }
  function reduce(key, values) {
    return Array.sum(values); // sum the ages
  },
  {
    query: { family: "Sharks" }, // query for sharks
    out: "sharkAges" // write to `sharkAges`
  }
);
```

You have to write two queries, a `map` and a `reduce` which filter the
dataset and then aggregate them into one value.

## Graph-Like Data Models

To represent a graph like data structure you represent it like so
relationally.

```sql
CREATE TABLE vertices (
  vertex_id   integer PRIMARY KEY,
  properties  json
);
CREATE TABLE edges (
  edge_id integer PRIMARY KEY,
  tail_vertex integer REFERENCES vertices (vertex_id),
  head_vertex integer REFERENCES vertices (vertex_id),
  label       text,
  properties  json
);
CREATE INDEX edges_tails ON edges (tail_vertex);
CREATE INDEX edges_heads ON edges (head_vertex);
```

## The Cypher Query Language

Cypher is a declarative query language for graph databases like Neo4j.

This query sets up Lucy as `BORN_IN` `Idaho`, and `Idaho` in `USA` and
`USA` in `NAmerica`.

```sql
CREATE
  (NAmerica:Location {name: 'North America', type: 'continent'}),
  (USA:Location {name: 'United States', type: 'country' }),
  (Idaho:Location {name: 'Idaho', type: 'state'}),
  (Lucy:Person {name: 'Lucy' }),
  (Idaho) -[:WITHIN]-> (USA) -[:WITHIN]-> (NAmerica),
  (Lucy) -[:BORN_IN]-> (Idaho)
```

This allows you to find people who were `BORN_IN` the US and `LIVES_IN`
Europe declaratively.

```sql
MATCH
  (person) -[:BORN_IN]-> () -[:WITHIN*0..]-> (us:Location {name: 'United States'})
  (person) -[:LIVES_IN]-> () -[:WITHIN*0..]-> (eu:Location {name: 'Europe' })
RETURN person.name
```

`*0..` means 0 or more times.

The equivalent SQL is much more difficult, and performance can be
variable.

## Triple-Stores and SPARQL

The triple-store model is like the graph version displayed above.

A triple is a tuple that is composed of (subject, predicate, object)

The third value may be another vertex or it may be a primitive type.

### RDF

RDF is an XML specification to realize the semantic web.

### The SPARQL query language

The SparQL language predates Cypher, and also operates on triples:

```sql
PREFIX : <urn:example:>

SELECT ?personName WHERE {
  ?person :name ?personName.
  ?person :bornIn / :within* / :name "United States".
  ?person :livesIn / :within* / :name "Europe".
}
```

### The Datalog query language

The datalog query language predates cypher, and is used to map facts to
values.

First, we set up our schema.

```sql
name(namerica, 'North America').
type(namerica, continent).

name(usa, 'United States').
type(usa, country).
within(usa, namerica).

name(idaho, 'Idaho').
type(idaho, state).
within(idaho, usa).

name(lucy, 'Lucy').
born_in(lucy, idaho).
```

Then we query the data:

```sql
-- A location has a Location -> Name
within_recursive(Location, Name) :- name(Location, Name).

-- recurse through (Location, Name) -> (Location, Name) until end of chain.
within_recursive(Location, Name) :- within(Location, Via),
                                    within_recursive(Via, Name).

-- Migrated is defined as a Person who is BornIn X and LivesIn Y.
migrated(Name, BornIn, LivingIn) :- name(Person, Name),
                                    born_in(Person, BornLoc),
                                    within_recursive(BornLoc, BornIn),
                                    lives_in(Person, LivingLoc),
                                    within_recursive(LivingLoc, LivingIn).

?- migrated(Who, 'United States', 'Europe')
```

Prev:
[reliable-scalable-and-maintainable-applications](reliable-scalable-and-maintainable-applications.md)
Next:
[storage-and-retrieval](storage-and-retrieval.md)
