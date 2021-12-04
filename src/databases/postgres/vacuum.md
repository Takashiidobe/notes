---
title: vacuum
---

# Vacuum

`VACUUM` reclaims storage occupied by dead tuples:

When a tuple becomes unreachable (dead) in a table, it isn\'t
automatically reclaimed until `VACUUM`ed.

`VACUUM ANALYZE` updates statistics for the table, which may allow some
indexes that were previously not used to be used, or vice-versa, for
more efficient querying.
