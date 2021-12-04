---
title: structured-query-language
---

Query Language"

# Structured Query Language

Next:
[software-architecture](software-architecture.md)

We first begin by loading in some data:

This loads in a csv file as a table called `factbook.csv` which is a tab
delimited dataset of Year, date, shares, trades, dollars. We cast this
from a text type into a bigint by replacing the dollar sign and commas
and replacing it with an int.

```sql
begin;

create table factbook
(
    year int,
    date date,
    shares text,
    trades text,
    dollars text
);

copy factbook from 'factbook.csv' with delimiter E't' null ''

alter table factbook
    alter shares
    type bigint
    using replace(shares, ',', '')::bigint,

    alter trades
    type bigint
    using replace(trades, ',', '')::bigint,

    alter dollars
    type bigint
    using substring(replace(dollars, ',', '')) from 2)::numeric;

commit;
```

## Application Code and sql

We can try and find all trades that happened in February 2017 like so:

```sql
select date,
    to_char(shares, '99G999G999G999') as shares,
    to_char(trades, '99G999G999') as trades,
    to_char(dollars, 'L99G999G999G999') as dollars
    from factbook
   where date >= date :'start'
     and date < date :'start' + interval '1month'
order by date;
```

We might want to create a function that can do this for us, but we have
to be wary of SQL injection.

We can create "prepared statements" which will do that for us:

```sql
prepare query as
    select date, shares, trades, dollars
    from factbook
    where date >= $1::date
    and date < $1::date + interval '1month'
    order by date;
```

And we can execute it like so:

```sql
execute query('2010-02-01');
```

We can create a chart that shows all trades on a the month:

```sql
select cast(calendar.entry as date) as date,
coalesce(shares, 0) as shares,
coalesce(trades, 0) as trades,
to_char(
    coalesce(dollars, 0),
    L99G999G999G999
) as dollars
from
    generate_series(
        date :'start',
        date :'start' + interval '1 month' - interval '1 day',
        interval '1 day'
    )
    as calendar(entry)
    left join factbook
        on factbook.date = calendar.entry
order by date;
```

Let's say we want to count week on week growth:

We can use a window function:

```sql
prepare foo as
 select date, shares, trades, dollars
   from factbook
  where date >= $1::date
    and date  < $1::date + interval '1 month'
  order by date;
execute foo('2010-02-01');
  select cast(calendar.entry as date) as date,
         coalesce(shares, 0) as shares,
         coalesce(trades, 0) as trades,
         to_char(
             coalesce(dollars, 0),
             'L99G999G999G999'
         ) as dollars
    from /*
          * Generate the target month's calendar then LEFT JOIN
          * each day against the factbook dataset, so as to have
          * every day in the result set, whether or not we have a
          * book entry for the day.
          */
         generate_series(date :'start',
                         date :'start' + interval '1 month'
                                       - interval '1 day',
                         interval '1 day'
         )
         as calendar(entry)
         left join factbook
                on factbook.date = calendar.entry
order by date;
with computed_data as
(
  select cast(date as date)   as date,
         to_char(date, 'Dy')  as day,
         coalesce(dollars, 0) as dollars,
         lag(dollars, 1)
           over(
             partition by extract('isodow' from date)
                 order by date
           )
         as last_week_dollars
    from /*
          * Generate the month calendar, plus a week before
          * so that we have values to compare dollars against
          * even for the first week of the month.
          */
         generate_series(date :'start' - interval '1 week',
                         date :'start' + interval '1 month'
                                       - interval '1 day',
                         interval '1 day'
         )
         as calendar(date)
         left join factbook using(date)
)
  select date, day,
         to_char(
             coalesce(dollars, 0),
             'L99G999G999G999'
         ) as dollars,
         case when dollars is not null
               and dollars <> 0
              then round(  100.0
                         * (dollars - last_week_dollars)
                         / dollars
                       , 2)
          end
         as "WoW %"
    from computed_data
   where date >= date :'start'
order by date;
```

Next:
[software-architecture](software-architecture.md)
