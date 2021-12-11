---
title: "Performance Schema"
---

# Performance Schema

Prev: [monitoring-in-a-reliability-engineering-world](monitoring-in-a-reliability-engineering-world.md)
Next: [operating-system-and-hardware-optimization](operating-system-and-hardware-optimization.md)

The performance schema provides metrics on operations in MySQL.

Querying Performance Schema involves `instruments` and `consumers`,
where `instruments` refer to code we want to capture information about,
and `consumers` which is a table that stores the information.

## Consumer Organization

### Current and Historical Data

Here are some groups of tables in `performance_schema`.

1. `*_current`
   Events that are occurring on the server at present

2. `*_history`
   Last 10 completed events per thread

3. `*_history_long`
   Last 10,000 completed events per thread, globally

And events:

1. `events_waits`
   Low-level server waits, such as acquiring mutexes
2. `events_statements`
   SQL statements
3. `events_stages`
   Profile information, such as creating temporary tables or sending data
4. `events_transactions`
   Transactions

There are summary tables that hold statistics on each of thesse events.

### Resource Consumption

Performance schema is held in memory: The amount of memory it consumes
can be toggled as well. Instrumentation has some cost on CPU usage. Some
events (like monitoring mutex lock/release) are particularly expensive.

### Limitations

1. MySQL must support instrumenting it.
2. It collects data after the instrument and consumer are enabled.
3. It is difficult to free memory.

## sys Schema

MySQL 5.7 has a sys schema performance, which contains views over
`performance_schema`.

### Threads

Performance schema can list all threads in the server:

```sql
SELECT NAME, THREAD_ID, PROCESSLIST_ID, THREAD_OS_ID
    -> FROM performance_schema.threads;
```

Which lists something like this:

```
+------------------------+-----------+----------------+--------------+
| NAME                   | THREAD_ID | PROCESSLIST_ID | THREAD_OS_ID |
+------------------------+-----------+----------------+--------------+
| thread/sql/main        |         1 |           NULL |       797580 |
| thread/innodb/io_ib... |         3 |           NULL |       797583 |
| thread/innodb/io_lo... |         4 |           NULL |       797584 |
...
| thread/sql/slave_io    |        42 |              5 |       797618 |
| thread/sql/slave_sql   |        43 |              6 |       797619 |
| thread/sql/event_sc... |        44 |              7 |       797620 |
| thread/sql/signal_h... |        45 |           NULL |       797621 |
| thread/mysqlx/accep... |        46 |           NULL |       797623 |
| thread/sql/one_conn... |     27823 |          27784 |       797695 |
| thread/sql/compress... |        48 |              9 |       797624 |
+------------------------+-----------+----------------+--------------+
```

## Configuration

Performance schema can be turned on or off by using setting it to `ON`
or `OFF` in a configuration file.

### Enabling and Disabling Instruments

Instruments can be queried in the `setup_instruments` table.

```sql
mysql> SELECT * FROM performance_schema.setup_instruments
    -> WHERE NAME='statement/sql/select'\G
*************************** 1. row ***************************
 NAME: statement/sql/select
 ENABLED: NO
 TIMED: YES
 PROPERTIES:
 VOLATILITY: 0
 DOCUMENTATION: NULL
```

It is currently turned off, but can be turned on:

```sql
mysql> UPDATE performance_schema.setup_instruments
    -> SET ENABLED='YES' WHERE NAME='statement/sql/select';
Query OK, 1 rows affected (0.00 sec)
Rows matched: 1 Changed: 1 Warnings: 0
```

Or, since this is SQL, turn on all SQL statement instruments

```sql
mysql> UPDATE performance_schema.setup_instruments
    -> SET ENABLED='YES' WHERE NAME LIKE statement/sql/%';
Query OK, 167 rows affected (0.00 sec)
Rows matched: 167 Changed: 167 Warnings: 0
```

Updating through SQL or a stored proc does not persist past restarts, so
enable performance schema in your configuration files.

## Enabling and Disabling Consumers

Consumers can be enabled by:

1. Updating the `setup_consumers` table in Performance Schema
2. Using the stored procedures `pssetup_enable_consumer` and `ps_setup disable_consumer` in sys schema
3. Setting the performance-schema-consumer configuration parameter

| Consumer                                                   | Description                                                                                                                                                                     |
| ---------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `events_stages_(current \| history \| history_long)`       | Profiling details, such as "Creating tmp table“, "statistics", or "buffer pool load"                                                                                            |
| `events_statements_(current \| history \| history_long)`   | Statements statistics                                                                                                                                                           |
| `events_transactions_(current \| history \| history_long)` | Transactions                                                                                                                                                                    |
| `events_waits_(current \| history \| history_long)`        | Waits                                                                                                                                                                           |
| `global_instrumentation`                                   | Enables or disables global instrumentation. If disabled, no individual parameters are checked and no global or per-thread data is maintained. No individual event is collected. |
| `thread_instrumentation`                                   | Per-thread instrumentation. Only checked if global instrumentation is enabled. If disabled, no per-thread or individual event data is collected.                                |
| `statements_digest`                                        | Statement digests                                                                                                                                                               |

Monitoring can be tuned for specific objects.

## Using Performance Schema

| Column                  | Description                                                                                                                                                                                                                                                          | Importance                    |
| ----------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ----------------------------- |
| CREATED_TMP_DISK_TABLES | The query created this number of disk-based temporary tables. You have two options to resolve this issue: optimize the query or increase maximum size for in-memory temporary tables.                                                                                | High                          |
| CREATED_TMP_TABLES      | The query created this number of memory-based temporary tables. Use of in-memory temporary tables is not bad per se. However, if the underlying table grows, they may be converted into disk-based tables. It is good to be prepared for such situations in advance. | Medium                        |
| SELECT_FULL_JOIN        | The JOIN performed a full table scan because there is no good index to resolve the query otherwise. You need to reconsider your indexes unless the table is very small.                                                                                              | High                          |
| SELECT_FULL_RANGE_JOIN  | If the JOIN used a range search of the referenced table.                                                                                                                                                                                                             | Medium                        |
| SELECT_RANGE            | If the JOIN used a range search to resolve rows in the first table. This is usually not a big issue.                                                                                                                                                                 | Low                           |
| SELECT_RANGE_CHECK      | If the JOIN is without indexes, which checks for keys after each row. This is a very bad symptom, and you need to reconsider your table indexes if this value is greater than zero.                                                                                  | High                          |
| SELECT_SCAN             | If the JOIN did a full scan of the first table. This is an issue if the table is large.                                                                                                                                                                              | Medium                        |
| SORT_MERGE_PASSES       | The number of merge passes that the sort has to perform. If the value is greater than zero and the query performance is slow, you may need to increase sort_buffer_size.                                                                                             | Low                           |
| SORT_RANGE              | If the sort was done using ranges.                                                                                                                                                                                                                                   | Low                           |
| SORT_ROWS               | The number of sorted rows. Compare with the value of the returned rows. If the number of sorted rows is higher, you may need to optimize your query.                                                                                                                 | Medium (see Description)      |
| SORT_SCAN               | If the sort was done by scanning a table. This is a very bad sign unless you purposely select all rows from the table without using an index.                                                                                                                        | High                          |
| NO_INDEX_USED           | No index was used to resolve the query.                                                                                                                                                                                                                              | High, unless tables are small |
| NO_GOOD_INDEX_USED      | Index used to resolve the query is not the best. You need to reconsider your indexes if this value is greater than zero.                                                                                                                                             | High                          |

We can use this table to figure out problematic queries:

Queries that didn't use a good index:

```sql
SELECT THREAD_ID, SQL_TEXT, ROWS_SENT, ROWS_EXAMINED, CREATED_TMP_TABLES,
NO_INDEX_USED, NO_GOOD_INDEX_USED
FROM performance_schema.events_statements_history_long
WHERE NO_INDEX_USED > 0 OR NO_GOOD_INDEX_USED > 0;
```

```sql
SELECT THREAD_ID, SQL_TEXT, ROWS_SENT, ROWS_EXAMINED, CREATED_TMP_TABLES,
CREATED_TMP_DISK_TABLES
FROM performance_schema.events_statements_history_long
WHERE CREATED_TMP_TABLES > 0 OR CREATED_TMP_DISK_TABLES > 0;
```

There are other views that are useful for finding statements that
require optimization:

| View                                        | Description                                                                                                                                                                                            |
| ------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| statement_analysis                          | A normalized statement view with aggregated statistics, ordered by the total execution time per the normalized statement. Similar to the events_statements_sum mary_by_digest table but less detailed. |
| statements_with_errors_or_warnings          | All normalized statements that raised errors or warnings.                                                                                                                                              |
| statements_with_full_table_scans.           | All normalized statements that have done a full table                                                                                                                                                  |
| scan.                                       |
| statements_with_runtimes_in_95th_percentile | All normalized statements whose average execution time is in the top 95th percentile.                                                                                                                  |
| statements_with_sorting                     | All normalized statements that have done sorts. The view includes all kinds of sorts.                                                                                                                  |
| statements_with_temp_tables                 | All normalized statements that used temporary tables.                                                                                                                                                  |

Prepared statements can also be instrumented:

| Instrument Class          | Description                                                            |
| ------------------------- | ---------------------------------------------------------------------- |
| statement/sql/prepare_sql | PREPARE statement in the text protocol (when run via MySQL CLI)        |
| statement/sql/execute_sql | EXECUTE statement in the text protocol (when run via MySQL CLI)        |
| statement/com/Prepare     | PREPARE statement in the binary protocol (if accessed via MySQL C API) |
| statement/com/Execute     | EXECUTE statement in the binary protocol (if accessed via MySQL C API  |

Event Stages is particularly useful:

| Stage Classes                                                                        | Description                                                                                                                                                                                                                                                                                                                                                                                                                        |
| ------------------------------------------------------------------------------------ | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| stage/sql/%tmp%                                                                      | Everything related to the temporary tables.                                                                                                                                                                                                                                                                                                                                                                                        |
| stage/sql/%lock%                                                                     | Everything related to locks.                                                                                                                                                                                                                                                                                                                                                                                                       |
| stage/%/Waiting for%                                                                 | Everything waiting for a resource.                                                                                                                                                                                                                                                                                                                                                                                                 |
| stage/sql/Sending data                                                               | This stage should be compared to the number of ROWS_SENT in the statements statistics. If ROWS_SENT is small, a statement spending a lot of time in this stage could mean that it has to create a temporary file or table to resolve intermediary results. This is often followed by filtering the rows before sending data to the client. This is usually a symptom of a badly optimized query.                                   |
| stage/sql/freeing items stage/sql/cleaning up stage/sql/closing tables stage/sql/end | These are stages that clean resources. Unfortunately, they are not detailed enough, and each of them includes more than a single task. If you see that your queries spend a long time in these stages, you most likely hit resource contention due to high concurrency. You need to check your CPU, I/O, and memory usage as well as whether your hardware and MySQL options can handle concurrency that your application creates. |

## Examining Read Versus Write Performance

To see the count of all events in performance schema:

```sql
mysql> SELECT EVENT_NAME, COUNT(EVENT_NAME)
    -> FROM events_statements_history_long
    -> GROUP BY EVENT_NAME;
+----------------------+-------------------+
| EVENT_NAME           | COUNT(EVENT_NAME) |
+----------------------+-------------------+
| statement/sql/insert |               504 |
| statement/sql/delete |               502 |
| statement/sql/select |              6987 |
| statement/sql/update |              1007 |
| statement/sql/commit |               500 |
| statement/sql/begin  |               500 |
+----------------------+-------------------+
6 rows in set (0.03 sec)
```

To see how long each event takes as an aggregate:

```sql
mysql> SELECT EVENT_NAME, COUNT(EVENT_NAME),
    -> SUM(LOCK_TIME/1000000) AS latency_ms
    -> FROM events_statements_history
    -> GROUP BY EVENT_NAME ORDER BY latency_ms DESC;
+----------------------------------+-------------------+------------+
| EVENT_NAME                       | COUNT(EVENT_NAME) | latency_ms |
+----------------------------------+-------------------+------------+
| statement/sql/select             |               194 |  7362.0000 |
| statement/sql/update             |                33 |  1276.0000 |
| statement/sql/insert             |                16 |   599.0000 |
| statement/sql/delete             |                16 |   470.0000 |
| statement/sql/show_status        |                 2 |   176.0000 |
| statement/sql/begin              |                 4 |     0.0000 |
| statement/sql/commit             |                 2 |     0.0000 |
| statement/com/Ping               |                 2 |     0.0000 |
| statement/sql/show_engine_status |                 1 |     0.0000 |
+----------------------------------+-------------------+------------+
9 rows in set (0.01 sec)
```

Or the bytes of rows read and written:

```sql
mysql> WITH rows_read AS (SELECT SUM(VARIABLE_VALUE) AS rows_read
    -> FROM global_status
    -> WHERE VARIABLE_NAME IN ('Handler_read_first', 'Handler_read_key',
    -> 'Handler_read_next', 'Handler_read_last', 'Handler_read_prev',
    -> 'Handler_read_rnd', 'Handler_read_rnd_next')),
    -> rows_written AS (SELECT SUM(VARIABLE_VALUE) AS rows_written
    -> FROM global_status
    -> WHERE VARIABLE_NAME IN ('Handler_write'))
    -> SELECT * FROM rows_read, rows_written\G
*************************** 1. row ***************************
rows_read: 169358114082
rows_written: 33038251685
1 row in set (0.00 sec)
```

To find information about Memory usage:

```sql
mysql> SELECT EVENT_NAME,
    -> CURRENT_NUMBER_OF_BYTES_USED/1024/1024 AS CURRENT_MB,
    -> HIGH_NUMBER_OF_BYTES_USED/1024/1024 AS HIGH_MB
    -> FROM performance_schema.memory_summary_global_by_event_name
    -> WHERE EVENT_NAME LIKE 'memory/innodb/%'
    -> ORDER BY CURRENT_NUMBER_OF_BYTES_USED DESC LIMIT 10;
+----------------------------+--------------+--------------+
| EVENT_NAME                 | CURRENT_MB   | HIGH_MB      |
+----------------------------+--------------+--------------+
| memory/innodb/buf_buf_pool | 130.68750000 | 130.68750000 |
| memory/innodb/ut0link_buf  |  24.00006104 |  24.00006104 |
| memory/innodb/buf0dblwr    |  17.07897949 |  24.96951294 |
| memory/innodb/ut0new       |  16.07891273 |  16.07891273 |
| memory/innodb/sync0arr     |   6.25006866 |   6.25006866 |
| memory/innodb/lock0lock    |   4.85086060 |   4.85086060 |
| memory/innodb/ut0pool      |   4.00003052 |   4.00003052 |
| memory/innodb/hash0hash    |   3.69776917 |   3.69776917 |
| memory/innodb/os0file      |   2.60422516 |   3.61988068 |
| memory/innodb/memory       |   1.23812866 |   1.42373657 |
+----------------------------+--------------+--------------+
10 rows in set (0,00 sec)
```

You can see the memory used by user:

```sql
mysql> SELECT thread_id tid, user,
    -> current_allocated ca, total_allocated
    -> FROM sys.memory_by_thread_by_current_bytes LIMIT 9;
+-----+----------------------------+------------+-----------------+
| tid | user                       | ca         | total_allocated |
+-----+----------------------------+------------+-----------------+
|  52 | sveta@localhost            | 1.36 MiB   | 10.18 MiB       |
|   1 | sql/main                   | 1.02 MiB   | 4.95 MiB        |
|  33 | innodb/clone_gtid_thread   | 525.36 KiB | 24.04 MiB       |
|  44 | sql/event_scheduler        | 145.72 KiB | 4.23 MiB        |
|  43 | sql/slave_sql              | 48.74 KiB  | 142.46 KiB      |
|  42 | sql/slave_io               | 20.03 KiB  | 232.23 KiB      |
|  48 | sql/compress_gtid_table    | 13.91 KiB  | 17.06 KiB       |
|  25 | innodb/fts_optimize_thread | 1.92 KiB   | 2.00 KiB        |
|  34 | innodb/srv_purge_thread    | 1.56 KiB   | 1.64 KiB        |
+-----+----------------------------+------------+-----------------+
9 rows in set (0,03 sec)
```

Or by thread:

```sql
mysql> SELECT * FROM sys.memory_by_thread_by_current_bytes
    -> ORDER BY current_allocated desc\G
*************************** 1. row ***************************
 thread_id: 152
 user: lj@127.0.0.1
 current_count_used: 325
 current_allocated: 36.00 GiB
 current_avg_alloc: 113.43 MiB
 current_max_alloc: 36.00 GiB
 total_allocated: 37.95 GiB
```

Or looking at variables that were changed dynamically:

```sql
mysql> SELECT * FROM performance_schema.variables_info
    -> WHERE VARIABLE_SOURCE = 'DYNAMIC'\G
*************************** 1. row ***************************
 VARIABLE_NAME: foreign_key_checks
 VARIABLE_SOURCE: DYNAMIC
 VARIABLE_PATH:
    MIN_VALUE: 0
    MAX_VALUE: 0
    SET_TIME: 2021-07-18 03:14:15.560745
    SET_USER: NULL
    SET_HOST: NULL
*************************** 2. row ***************************
 VARIABLE_NAME: sort_buffer_size
 VARIABLE_SOURCE: DYNAMIC
 VARIABLE_PATH:
    MIN_VALUE: 32768
    MAX_VALUE: 18446744073709551615
    SET_TIME: 2021-07-19 02:37:11.948190
    SET_USER: sveta
    SET_HOST: localhost
2 rows in set (0,00 sec)
```

## Examining Errors

Performance schema provides digest tables:

```sql
mysql> USE performance_schema;
mysql> SHOW CREATE TABLE events_errors_summary_global_by_error\G
*************************** 1. row ***************************
    Table: events_errors_summary_global_by_error
Create Table: CREATE TABLE `events_errors_summary_global_by_error` (
 `ERROR_NUMBER` int DEFAULT NULL,
 `ERROR_NAME` varchar(64) DEFAULT NULL,
 `SQL_STATE` varchar(5) DEFAULT NULL,
 `SUM_ERROR_RAISED` bigint unsigned NOT NULL,
 `SUM_ERROR_HANDLED` bigint unsigned NOT NULL,
 `FIRST_SEEN` timestamp NULL DEFAULT '0000-00-00 00:00:00',
 `LAST_SEEN` timestamp NULL DEFAULT '0000-00-00 00:00:00',
 UNIQUE KEY `ERROR_NUMBER` (`ERROR_NUMBER`)
) ENGINE=PERFORMANCE_SCHEMA DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci
1 row in set (0,00 sec)
```

Prev: [monitoring-in-a-reliability-engineering-world](monitoring-in-a-reliability-engineering-world.md)
Next: [operating-system-and-hardware-optimization](operating-system-and-hardware-optimization.md)
