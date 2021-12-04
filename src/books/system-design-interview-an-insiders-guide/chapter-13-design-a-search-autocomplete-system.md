---
title: "chapter 13 design a search autocomplete system"
---

# chapter 13 design a search autocomplete system

Prev: [chapter-12-design-a-chat-system](chapter-12-design-a-chat-system.md)
Next: [chapter-14-design-youtube](chapter-14-design-youtube.md)

This chapter outlines autocomplete, which is used at Google and Amazon.

Make sure to ask questions about the problem and scope:
Q: Is the matching only supported at the beginning of a search query or in the
middle as well?
A: Only at the beginning of a search query.
Q: How many autocomplete suggestions should the system return?
A: 5
Q: How does the system know which 5 suggestions to return?
A: This is determined by popularity, decided by the historical query frequency.
Q: Does the system support spell check?
A: No, spell check or autocorrect is not supported.
Q: Are search queries in English?
A: Yes. If time allows at the end, we can discuss multi-language support.
Q: Do we allow capitalization and special characters?
A: No, we assume all search queries have lowercase alphabetic characters.
Q: How many users use the product?
A: 10 million DAU.

## Back of the Envelope Estimation

- Assuming 10 million daily active users (DAU)
- An average person performs 10 searches per day
- 20 bytes of data per query string:
- For every character entered in the search box, the client sends a network request.
- ~ 24000 QPS = 10M users _ 10 queries/day _ 20 characters / 24 hours / 3600 seconds.
- Peak QPS is double the normal QPS, ~48,000 QPS.
- Assume 20% of the daily queries are new. 10M _ 10 queries/day _ 20 bytes per query * 20% = 0.4 GB. 0.4GB of new data is added to storage daily.

## High level design

Split the system into two parts:

- Data gathering
- Query service

### Data gathering service

As we query a new keyword, we add it into the database, along with its frequency (imagine a hashmap of key -> hit count).

```rs
use std::collections::HashMap;

let mut map = HashMap::new();
let count = map.entry(&str).or_insert(0);
*count += 1;
```

We can query the DB with SQL:

```sql
SELECT * FROM queries
where query like `prefix%`
ORDER BY frequency DESC
LIMIT 5;
```

This works fine for small datasets but hits a bottleneck in larger datasets.

Prev: [chapter-12-design-a-chat-system](chapter-12-design-a-chat-system.md)
Next: [chapter-14-design-youtube](chapter-14-design-youtube.md)
