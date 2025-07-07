---
title: API Design
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Sunday, July 6th 2025, 8:42:32 pm
---

# API Design

## Pagination

- Pagination is used to split up responses that might otherwise
  overwhelm the client or server, by splitting a request into smaller
  pieces.
- It can be implemented using offsets and cursors.

### Offset Based Pagination

- Use `LIMIT`, `WHERE`, `OFFSET` to generate a page listing.

  ```sql
  SELECT * FROM users
  WHERE team_id = %team_id
  ORDER BY id DESC
  LIMIT 20 OFFSET 40;
  ```

- You can count the number of pages:

  ```sql
  SELECT COUNT(*) AS total FROM users WHERE team_id = %team_id;
  ```

- This is simple, but doesn\'t scale, as the database has to read data
  up to the offset + count of rows from disk, and then do a filter.

- This is almost always a `SEQ SCAN`, which is I/O heavy.

- If items are being rewritten to the dataset or updated frequently,
  the window becomes unreliable, skipping, or returning duplicate
  results.

### Cursor Based Pagination

- To use a cursor, rows must have a unique, sequential column in the
  source table.
- There is no concept of total number of pages in the set.
- The client can\'t jump to a specific page.

1.  Pick a unique, sequential column to paginate on.

2.  The client requests for a table and the count of items they want
    from it.

3.  The server queries for the count + 1 item:

    ```sql
    SELECT * FROM users
    WHERE team_id = $(team_id)
    ORDER BY id DESC
    LIMIT $(count + 1)
    ```

4.  and returns a response like so:

    ```json
    {
      "data": ["..."],
      "next_cursor": "123456" // user id of extra result.
    }
    ```

5.  The client then provides the `next_cursor` as `cursor` in the second
    request.

    ```sql
    SELECT * FROM users
    WHERE team_id = $(team_id)
    AND id <= $(cursor)
    ORDER BY id DESC
    LIMIT $(count + 1)
    ```

- This uses a `where` on a column that is easily indexable, which
  means the query planner doesn\'t have to look at rows it doesn\'t
  need to.
- As well, if there are common writes, the overall position of the
  cursor might change, but the pagination window adjusts accordingly.

## CRUD (Create, Read, Update, Delete)

- Create (POST in HTTP) is to create a resource. It is not idempotent.
- Read (GET in HTTP) is used to read a resource. It is cacheable, as
  long as the underlying resource hasn\'t changed.
- Update (PUT/PATCH in HTTP) is used to update an existing resource.
  It is possibly idempotent.
- Delete (DELETE in HTTP) is used to delete an existing resource.

Prev:
[security-and-https](security-and-https.md)
