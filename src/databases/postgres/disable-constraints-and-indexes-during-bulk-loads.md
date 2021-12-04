---
title: disable-constraints-and-indexes-during-bulk-loads
---

Constraints And Indexes During Bulk Loads

# Disable Constraints and Indexes During Bulk Loads

During a bulk load, you\'ll want to add constraints to the table after
it\'s been loaded, not before:

If you do have constraints on a table beforehand, you\'ll pay a penalty
when trying to expand the table:

Take this schema:

```sql
DROP TABLE IF EXISTS product CASCADE;
CREATE TABLE product (
    id serial PRIMARY KEY,
    name TEXT NOT NULL,
    price INT NOT NULL
);
INSERT INTO product (name, price)
    SELECT random()::text, (random() * 1000)::int
    FROM generate_series(0, 10000);


DROP TABLE IF EXISTS customer CASCADE;
CREATE TABLE customer (
    id serial PRIMARY KEY,
    name TEXT NOT NULL
);
INSERT INTO customer (name)
    SELECT random()::text
    FROM generate_series(0, 100000);


DROP TABLE IF EXISTS sale;
CREATE TABLE sale (
    id serial PRIMARY KEY,
    created timestamptz NOT NULL,
    product_id int NOT NULL,
    customer_id int NOT NULL
);
```

First we add our constraints and indexes on it:

```sql
db= ALTER TABLE sale ADD CONSTRAINT sale_product_fk
db- FOREIGN KEY (product_id) REFERENCES product(id);
ALTER TABLE
Time: 18.413 ms

db= ALTER TABLE sale ADD CONSTRAINT sale_customer_fk
db- FOREIGN KEY (customer_id) REFERENCES customer(id);
ALTER TABLE
Time: 5.464 ms

db= CREATE INDEX sale_created_ix ON sale(created);
CREATE INDEX
Time: 12.605 ms

db= INSERT INTO SALE (created, product_id, customer_id)
db- SELECT
db-    now() - interval '1 hour' * random() * 1000,
db-    (random() * 10000)::int + 1,
db-    (random() * 100000)::int + 1
db- FROM generate_series(1, 1000000);
INSERT 0 1000000
Time: 15410.234 ms (00:15.410)
```

Inserting 1 million rows takes 15 seconds.

Next, if we flip the order, the constraints do take longer, but the data
loading is much shorter:

```sql
db= INSERT INTO SALE (created, product_id, customer_id)
db- SELECT
db-    now() - interval '1 hour' * random() * 1000,
db-    (random() * 10000)::int + 1,
db-    (random() * 100000)::int + 1
db- FROM generate_series(1, 1000000);
INSERT 0 1000000
Time: 2277.824 ms (00:02.278)

db= ALTER TABLE sale ADD CONSTRAINT sale_product_fk
db- FOREIGN KEY (product_id) REFERENCES product(id);
ALTER TABLE
Time: 169.193 ms

db= ALTER TABLE sale ADD CONSTRAINT sale_customer_fk
db- FOREIGN KEY (customer_id) REFERENCES customer(id);
ALTER TABLE
Time: 185.633 ms

db= CREATE INDEX sale_created_ix ON sale(created);
CREATE INDEX
Time: 484.244 ms
```

In Postgres, there\'s no way to disable indexes, so you\'ll have to drop
them and recreate them.
