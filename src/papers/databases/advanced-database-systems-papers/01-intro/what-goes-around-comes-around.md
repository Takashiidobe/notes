---
title: "What Goes Around Comes Around"
pdf_url: "[[what-goes-around-comes-around.pdf]]"
---
## Notes

This paper discusses 35 years of Data model proposals, starting from the 60s to the present.

- Hierarchical (IMS): late 1960’s and 1970’s 
- Network (CODASYL): 1970’s 
- Relational: 1970’s and early 1980’s 
- Entity-Relationship: 1970’s 
- Extended Relational: 1980’s 
- Semantic: late 1970’s and 1980’s 
- Object-oriented: late 1980’s and early 1990’s 
- Object-relational: late 1980’s and early 1990’s 
- Semi-structured (XML): late 1990’s to the present

## Hierarchical (IMS)

The IMS era had a hierarchical data model, which was represented as a tree. That meant that each record, outside of the root, must have a parent, and querying was done by querying through the tree. 

There are a few cons:
- Information is repeated (non-normal)
- Existence depends on parents 
- Physical data dependence (an application must know the underlying data representation), and the author must do manual query optimization. 

Lesson 1: Physical and logical data independence are highly desirable 
Lesson 2: Tree structured data models are very restrictive 
Lesson 3: It is a challenge to provide sophisticated logical reorganizations of tree structured data 
Lesson 4: A record-at-a-time user interface forces the programmer to do manual query optimization, and this is often hard.
## CODASYL

Records are organized in a graph (multiple parents are possible), however, there must be at least one entry point, a record that is not a child.

Graphs allow for easier modeling without requiring parents, but had problems because it required keeping track of navigation in bookkeeping, + poorer logical and physical data independence.

Lesson 5: Networks are more flexible than hierarchies but more complex 
Lesson 6: Loading and recovering networks is more complex than hierarchies
## Relational

Codd proposed the relational model with three points:
1.  Store data simply in tables
2. Access it through a high-level DML
3. No need to know the physical storage layer

This allowed for physical data independence, query optimization, and allowed easier data modeling than previous versions.

In the end this won out because of the minicomputer revolution, where IBM eventually blessed DB/2 and the relational model became commercially popular.

Lesson 7: Set-a-time languages are good, regardless of the data model, since they offer much improved physical data independence. 
Lesson 8: Logical data independence is easier with a simple data model than with a complex one. 
Lesson 9: Technical debates are usually settled by the elephants of the marketplace, and often for reasons that have little to do with the technology. Lesson 10: Query optimizers can beat all but the best record-at-a-time DBMS application programmers
## The Entity-Relationship Era

Peter Chen proposed this model in the 70s. 

- The database should be a collection of instances of **entities**. 
- **Entities** have **attributes**, which **characterize** the entity. 
- One or more of these would be unique, the **primary key**.
- There are **relationships** between entities, like 1-1, 1-n, n-1, m-n.

While it was never picked up steam as a DBMS language, we use this idea often in database modeling today, and this is pretty much 3NF.

Also seems related to entity component systems in game design today. Turned out to be quite fruitful in database design and elsewhere.

Lesson 11: Functional dependencies are too difficult for mere mortals to understand. Another reason for KISS (Keep it simple stupid).

## R++ Era

These were additions to the relational model. Some common additions:

1. set-value attributes: some types take a list or set of items. That should be a first class construct.
2. aggregation: tuples should be embedded/referenced. This allows easier querying without joins:
```sql
Select Supply.SR.sno From Supply Where Supply.PT.pcolor = "red"
```
3. generalization: supporting inheritance, basically.

These ideas didn't get that popular.

Lesson 12: Unless there is a big performance or functionality advantage, new constructs will go nowhere.

## The OO Era

With popular OO languages like C++, people wanted an OOP querying language to follow suit.

Basically allowing you to persist data from C++ as is in a database. However, this also didn't get very far as there were no companies offering this support.

## The Object Relational Model

INGRES was having trouble supporting a pure relational model for GIS like problems: B-trees and primitive types couldn't support more complex use cases like notifying users in a 2-D space, and B-trees naturally cannot query more than 1-D space.

This required adding:

1. User-defined types
2. User defined operators
3. User defined functions
4. User defined access methods

This worked out pretty well and I'd say is having a resurgence after its first wave in the 90s -- there's lots of products that use postgres' UDF functionality to extend it, including PostGIS from the 90s, but even ParadeDB in 2024 to have elasticsearch like functionality in the DB.

## Semi Structured Data

Similarly to the XML/JSON databases of today, that a schema is not required in advance. Elasticsearch also maps onto this paradigm. However, this can be difficult to maintain due to records having mismatched types, data, and it can be difficult to optimize queries where the bits aren't in a structured format.