---
title: row-level-security
---

Level Security

# Row Level Security

```sql
CREATE TABLE test (
  id SERIAL PRIMARY KEY,
  username TEXT DEFAULT current_user,
  message TEXT
);

ALTER TABLE test ENABLE ROW LEVEL SECURITY;

CREATE POLICY test_policy on test USING (username = current_user);
```

```sql
CREATE ROLE test_user_1;
grant all on test to test_user_1;


CREATE ROLE test_user_2;
grant all on test to test_user_2;
```

```sql
SET ROLE test_user_1;
INSERT INTO test (message) VALUES ('Test user 1 says hi');

SELECT * from test;
```

```sql
SET ROLE test_user_2;
INSERT INTO TABLE test(message) VALUES ('Test User 2 Says Hi');

SELECT * from test;

SELECT COUNT(*) from test;
```

```sql
set role test_user_1;

SELECT * from test;
SELECT COUNT(*) from test;
```
