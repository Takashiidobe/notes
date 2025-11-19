---
title: "How Not To Structure Your Database Your Database Backed Web Applications A Study Of Performance Bugs In The Wild"
pdf_url: "[[how-not-to-structure-your-database-your-database-backed-web-applications-a-study-of-performance-bugs-in-the-wild.pdf]]"
---
This paper looks at 12 open-source rails apps that are primarily database driven and asks 3 questions:

1. How well do real-world DB backed web apps scale as data grows?
2. What are the common anti-patterns behind performance + scalability bugs?
3. How effective and hard are fixes? Can they be automated?

The 12 apps across 6 categories include discourse, gitlab, spree, openstreemap, and lobsters, all of which were open source.
The DBs are seeded with realistic contents from statistics from public deployments. Each app gets either 200, 2,000, or 20,000 rows in the main table, with related tables scaled accordingly. Seems kind of small -- but the authors note that almost all apps still had 2 second load times even with this little data.
They then profiled each application using chrome-based crawlers on AWS, and collected end-to-end latency + server-side metrics from rails, and then discussed the interesting stuff.
As well, there was a meta analysis of performance related issues on these open-source projects.

## How bad is performance?

- The 10 slowest pages with the 20k row setup were taken per app.
- 11/12 applications had >2s E2E latency, and 6 have >3s latency.
- Server-time is more than 40% of E2E latency. 50% of the slow pages spend >80% of their time in rails.

## Nine recurring ORM performance anti-patterns

1. Inefficient Computation
	- `any?` vs `exists?` - any always has to look through the entire query set, whereas `exists?` short circuits.
	- `where(...).first` vs `find_by(...)`. The where adds an unnecessary ORDER BY on the condition, which can lead to a file sort in worst case.
	- `pluck(...).sum)` vs `sum(...)` in SQL. native ops are faster in the RDBMS.
2. Unnecessary Computation
	- Loop-invariant queries: work is done inside a loop/query that can be done once outside. Hoist it. This is a bit tricky cause compilers optimize loop invariant code motion, so most programmers are used to this being optimized in code, but this isn't the case in a web app.
	- Dead stores: reloading an object (`order.reload`) even though it's not used between reloads. This would also be optimized by a compiler so it's not surprising this is a common problem.
3. Inefficient Data Access
	- N + 1 queries -- many questions instead of using eager loading with `includes(...)`
	- over eager-loading: eager loading to avoid N + 1s and freezing the app.
	- Issuing many `update` calls instead of using `update_all`.
4. Unnecessary Data Retrieval
	- Fetching columns or rows never used, e.g. `map(&:id)` instead of `pluck(:id)`.
5. Inefficient Rendering	
	- Use of partial views that call slow helpers per item.
6. Missing Fields
	- Derived values recomputed on every request instead of being materialized as a column. For OSM, computing a `location_name` instead of storing it reduced action time from ~1s to 0.36s.
7. Missing Indexes
	- Slow queries due to missing indexes
8. Content Display Trade-offs
	- Displaying all records in one page without pagination
	- Fast for small sets but brutally slow for large sets
9. Functionality Trade-offs
	- e.g. a sidebar that loads all related objects for a user. This is expensive for the DB.
## How Effective are Fixes?

- Median change improved latency by **~2x**. **>60%** of fixes gave more than a **2x** speedup. Some gave a **>5x** speedup, and one was **40x**.
- Across the fixes, server-time went from **~3.5s** to **~0.7s**.
- Code churn was small -- **~80%** of the changes touched **<5 loc**. 

## How does static chekcing fare?

- The authors implemented a static checker for the 9 misuse patterns, and found 430 instances. 50 were confirmed and 30 were fixed by the time the paper was published.