---
title: business-logic
---

Logic"

# Business Logic

Prev:
[getting-ready-to-read-this-book](getting-ready-to-read-this-book.md)
Next:
[a-small-application](a-small-application.md)

How much business logic should we put in the database?

Let's query the chinook database for an artist's albums and total
duration of each album:

```sql
select album.title as album
    sum(milliseconds) * interval '1ms' as duration
    from album
        join artist using(artistid)
        left join track using (albumid)
    where artist.name = 'Red Hot Chili Peppers'
group by album
order by album;
```

## Correctness

There are four isolation levels in Postgres:

- Read uncommitted:
- Read committed:
  - This allows transactions to see the results of other
    transactions as soon as they are committed.
- Repeatable Read
  - Your transaction uses the same snapshot of the whole database
    for its entire duration, from `BEGIN` to `COMMIT`. This means
    that even if a transaction is going on in the background, it
    won't affect this query.
- Serializable
  - This guarantees that there is a one-transaction-at-a-time
    ordering of what query was run.

## Stored Procedures

We can create a function that will allow us to do the same query but
with the artist_id.

```sql
create or replace function get_all_albums
(
    in artistid bigint,
    out album text,
    out duration interval
);
returns setof record
language sql
as $$
    select album.title as album,
    sum(milliseconds) * interval '1 ms' as duration
    from album
        join artist using(artistid)
        left join track using(albumid)
        where artist.artistid = get_all_albums.artistid
group by album
order by album;
$$
```

try to use SQL only instead of PLpgSQL, although you can do that if
necessary.

Prev:
[getting-ready-to-read-this-book](getting-ready-to-read-this-book.md)
Next:
[a-small-application](a-small-application.md)
