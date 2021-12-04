---
title: anomaly-detection-with-stats
---

Detection With Stats

# Anomaly Detection with Statistics

## Using Standard Deviation

Taking this series of numbers:

`2, 3, 5, 2, 3, 12, 5, 3, 4`

We can see that the outlier is 12. Every other number is between 2 and 5.

We can find a good center point by finding the average of the array:

```sql
SELECT avg(n)
FROM unnest(array[2, 3, 5, 2, 3, 12, 5, 3, 4]) AS n;

       avg
────────────────────
4.3333333333333333
```

We can also use the median here, since it\'s less weighted by extremes:

```sql
SELECT percentile_disc(0.5) within group(order by n)
FROM unnest(ARRAY[2, 3, 5, 2, 3, 120, 5, 3, 4]) as n;

 median
────────
      3
```

Next, we can find the standard deviation:

```sql
SELECT stddev(n)
FROM unnest(array[2, 3, 5, 2, 3, 12, 5, 3, 4]) AS n;

      stddev
────────────────────
3.0822070014844882
```

We can find out which numbers are outside the stddev and avg like so:

```sql
WITH series AS (
   SELECT *
   FROM unnest(array[2, 3, 5, 2, 3, 12, 5, 3, 4]) AS n
),
bounds AS (
   SELECT
       avg(n) - stddev(n) AS lower_bound,
       avg(n) + stddev(n) AS upper_bound
   FROM
       series
)
SELECT
   n,
   n NOT BETWEEN lower_bound AND upper_bound AS is_anomaly
FROM
   series,
   bounds;

n  │ is_anomaly
───┼────────────
 2 │ f
 3 │ f
 5 │ f
 2 │ f
 3 │ f
12 │ t
 5 │ f
 3 │ f
 4 │ f
```

We can also use the `MAD`, or Median absolute deviation to find
anomalies instead of an average + stddev. `MAD` calculates the amount of
medians

Consider the dataset here:

`1, 1, 2, 2, 4, 6, 9`

This has a median of 2:

The absolute deviations from 2 are as follows:

`0, 0, 1, 1, 2, 4, 7`

We see that the median of these values is again 1. The `MAD` for this
data is 1, so we see that 4 is 2 deviations away, and 9 is 7 deviations
away.

## Using Z-Score

We can use Z-Score to do this as well:

Z-Score represents the amount of Standard Deviations away from the mean
a certain item is:

```sql
WITH series AS (
   SELECT *
   FROM unnest(array[2, 3, 5, 2, 3, 12, 5, 3, 4]) AS n
),
stats AS (
   SELECT
       avg(n) series_mean,
       stddev(n) as series_stddev
   FROM
       series
)
SELECT
   n,
   (n - series_mean) / series_stddev as zscore
FROM
   series,
   stats;

n  │         zscore
───┼─────────────────────────
 2 │ -0.75703329861022517346
 3 │ -0.43259045634870009448
 5 │  0.21629522817435006346
 2 │ -0.75703329861022517346
 3 │ -0.43259045634870009448
12 │      2.4873951240050256
 5 │  0.21629522817435006346
 3 │ -0.43259045634870009448
 4 │ -0.10814761408717501551
```

As we can see, 12 is more than 1 stddev away from the mean, so we know
it\'s anomalous.

We can change this a bit to see if something is anomalous in .5 stddev,
1 stddev, and 3 stddev.

```sql
WITH series AS (
   SELECT *
   FROM unnest(array[2, 3, 5, 2, 3, 12, 5, 3, 4]) AS n
),
stats AS (
   SELECT
       avg(n) series_avg,
       stddev(n) as series_stddev
   FROM
       series
),
zscores AS (
   SELECT
       n,
       (n - series_avg) / series_stddev AS zscore
   FROM
       series,
       stats
)
SELECT
   *,
   zscore NOT BETWEEN -0.5 AND 0.5 AS is_anomaly_0_5,
   zscore NOT BETWEEN -1 AND 1 AS is_anomaly_1,
   zscore NOT BETWEEN -3 AND 3 AS is_anomaly_3
FROM
   zscores;
n  │         zscore          │ is_anomaly_0_5 │ is_anomaly_1 │ is_anomaly_3
───┼─────────────────────────┼────────────────┼──────────────┼──────────────
 2 │ -0.75703329861022517346 │ t              │ f            │ f
 3 │ -0.43259045634870009448 │ f              │ f            │ f
 5 │  0.21629522817435006346 │ f              │ f            │ f
 2 │ -0.75703329861022517346 │ t              │ f            │ f
 3 │ -0.43259045634870009448 │ f              │ f            │ f
12 │      2.4873951240050256 │ t              │ t            │ f
 5 │  0.21629522817435006346 │ f              │ f            │ f
 3 │ -0.43259045634870009448 │ f              │ f            │ f
 4 │ -0.10814761408717501551 │ f              │ f            │ f
```

Let\'s say we want to check if we have a server problem with pure SQL
statistics:

500 => problem on the server? 400 => problem with clients? 404 =>
problem with SEO or redirects? 200 => significant traffic or DOS attack?

Create a table to store statistics:

```sql
CREATE TABLE server_log_summary AS (
   period timestamptz,
   status_code int,
   entries int
);
```

We can create an axis to join to with a CTE (Common Table Expression)

```sql
-- Correct!
WITH axis AS (
   SELECT
       status_code,
       generate_series(
           date_trunc('minute', now()),
           date_trunc('minute', now() - interval '1 hour'),
           interval '1 minute' * -1
       ) AS period
   FROM (
       VALUES (200), (400), (404), (500)
   ) AS t(status_code)
)
SELECT
   a.period,
   a.status_code,
   count(*) AS entries
FROM
   axis a
   LEFT JOIN server_log l ON (
       date_trunc('minute', l.timestamp) = a.period
       AND l.status_code = a.status_code
   )
GROUP BY
   period,
   status_code;
```

We might try to use the Z-Score to find out if we have an anomaly:

```sql
db= WITH stats AS (
   SELECT
       status_code,
       (MAX(ARRAY[EXTRACT('epoch' FROM period), entries]))[2] AS last_value,
       AVG(entries) AS mean_entries,
       STDDEV(entries) AS stddev_entries
   FROM
       server_log_summary
   WHERE
       -- In the demo data use:
       -- period > '2020-08-01 17:00 UTC'::timestamptz
       period > now() - interval '1 hour'
   GROUP BY
       status_code
)
SELECT * FROM stats;

status_code │ last_value │      mean_entries      │     stddev_entries
────────────┼────────────┼────────────────────────┼────────────────────────
        404 │          0 │ 0.13333333333333333333 │ 0.34280333180088158345
        500 │          0 │ 0.15000000000000000000 │ 0.36008473579027553993
        200 │       4084 │  2779.1000000000000000 │       689.219644702665
        400 │         24 │ 0.73333333333333333333 │     3.4388935285299212
```

We then calculate if this is anomalous by checking the difference
between the previous value:

```sql
db= WITH stats AS (
   SELECT
       status_code,
       (MAX(ARRAY[EXTRACT('epoch' FROM period), entries]))[2] AS last_value,
       AVG(entries) AS mean_entries,
       STDDEV(entries) AS stddev_entries
   FROM
       server_log_summary
   WHERE
       -- In the demo data use:
       -- period > '2020-08-01 17:00 UTC'::timestamptz
       period > now() - interval '1 hour'
   GROUP BY
       status_code
)
SELECT
   *,
   (last_value - mean_entries) / NULLIF(stddev_entries::float, 0) as zscore
FROM
   stats;

status_code │ last_value │ mean_entries │ stddev_entries │  zscore
────────────┼────────────┼──────────────┼────────────────┼────────
        404 │          0 │ 0.133        │ 0.3428         │ -0.388
        500 │          0 │ 0.150        │ 0.3600         │ -0.416
        200 │       4084 │ 2779.100     │ 689.2196       │  1.893
        400 │         24 │ 0.733        │ 3.4388         │  6.765
```

Clearly the 400s are anomalous, and also, we seem to have a bunch more
200s than normal.
