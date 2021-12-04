---
title: use-hashing-to-reduce-disk-usage
---

Hashing To Reduce Disk Usage

# Use Hashing to Reduce Disk Usage

The sort is fast, but it takes 30MB of disk space:

```sql
WindowAgg (cost=69547.50..79494.14 rows=497332 width=40) (actual time=107.619..152.457 rows=39160)
  Buffers: shared hit=3916, temp read=3807 written=3816
  -> Sort (cost=69547.50..70790.83 rows=497332 width=36) (actual time=107.607..127.485 rows=39160)
    Sort Key: blob, id
    Sort Method: external merge  Disk: 30456kB
    Buffers: shared hit=3916, temp read=3807 written=3816
    -> Seq Scan on dumps (cost=0..8889.32 rows=497332 width=36) (actual time=0.022..8.747 rows=39160)
      Buffers: shared hit=3916

Execution time: 159.960 ms
```

We can figure out the average size of the sort key:

```sql
> select avg(pg_column_size(blob)) from dumps;

   avg
----------
   780
```

780 is pretty large, and we could do better by hashing: Let\'s hash the
sort key:

```sql
> select avg(pg_column_size(md5(array_to_string(blob, '')))) from dumps;

    avg
-----------
    36
```

If we sort here:

```sql
SELECT
      id,
      MIN(id) OVER (
            PARTITION BY md5(array_to_string(blob, '')
      ) ORDER BY id)
FROM
      dumps;
```

The execution plan uses much less memory:

```sql
WindowAgg (cost=7490.74..8469.74 rows=39160 width=40) (actual time=349.394..371.771 rows=39160)
  Buffers: shared hit=3916
  -> Sort (cost=7490.74..7588.64 rows=39160 width=36) (actual time=349.383..353.045 rows=39160)
    Sort Key: (md5(array_to_string(blob, ''::text))), id
    Sort Method: quicksort  Memory: 4005kB
    Buffers: shared hit=3916
    -> Seq Scan on dumps (cost=0..4503.40 rows=39160 width=36) (actual time=0.055..292.070 rows=39160)
      Buffers: shared hit=3916

Execution time: 374.125 ms
```

In postgres, the `md5` function results in a 32-bit string:

```sql
select pg_column_size( md5('foo') ) as md5_size

md5_size
-------------
32
```

We can represent this in bytes using `bytea`.

```sql
create extension pgcrypto;
select pg_column_size( digest('foo', 'md5') ) as crypto_md5_size

crypto_md5_size
---------------
20
```

We can make this fit into its original 16-bits by casting it to the uuid
type:

```sql
select pg_column_size( uuid_in(md5('foo')::cstring) ) as uuid_size

uuid_size
---------------
16
```

Here is the size of each key with its disk usage:

expression size disk used

---

blob 780 309MB
md5(blob) 36 11MB
uuid_in(md5(blob)) 16 7MB

Here\'s the runtime:

The hashing is much slower since it takes some CPU time to hash, but we
use considerably less data, so that\'s the plus.

Query Runtime

---

blob 160ms
hashed blob 374ms
