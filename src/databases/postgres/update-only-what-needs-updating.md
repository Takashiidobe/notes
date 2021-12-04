---
title: update-only-what-needs-updating
---

Only What Needs Updating

# Update Only What Needs Updating

Let\'s take the example of normalizing an e-mail column:

```sql
db= UPDATE users SET email = lower(email);
UPDATE 1010000
Time: 1583.935 ms (00:01.584)
```

But what happens if the email address is already all lowercase? We\'ve
done some extra work for nothing.

To counter this, let\'s add a `WHERE` clause, so the database knows it
doesn\'t have to do an update on some columns:

\~5 times faster!

```sql
db= UPDATE users SET email = lower(email)
db- WHERE email != lower(email);
UPDATE 10000
Time: 299.470 ms
```
