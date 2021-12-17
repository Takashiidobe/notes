---
title: "MySQL in the Cloud"
---

# MySQL in the Cloud

Prev: [scaling-mysql](scaling-mysql.md)
Next: [compliance-with-mysql](compliance-with-mysql.md)

Managed MySQL is more hands-off, more expensive and gives you less
control.

Remember that these data-stores are probably `mysql` compatible, so they
might not even be MySQL under the hood.

## Amazon Aurora for MySQL

Aurora is a MySQL compatible hosted database (for MySQL 5.6). Aurora
separates compute from storage, which allows them to scale separately
and more flexibly. It takes snapshot backups, manages fast schema
changes, does audit logging, and manages replication within a single
region.

Aurora's replication is, however, entirely proprietary.

Here are some other offerings it has:

Aurora Serverless:

- This removes the long-running compute and leverages Amazon's serverless
  platform to serve the compute layer of the database.

Aurora Global Database:

- This puts your Aurora database in multiple regions.

Aurora Multi-Master

- This allows for more write capability by having more than one server
  accept writes.

## GCP Cloud SQL

GCP actually runs the community server of MySQL, but with certain
features disabled.

1. `SUPER` is diabled
2. Plugins are dissabled
3. `mysqldump` and `mysqlimport` are disabled.

However, there's a few pros:

1. Native high-availability
2. Encryption at rest
3. Flexibly managed upgrades using multiple methods

## MySQL on Virtual Machines

You'll need to think about what's the right machine type for you and
think about the following factors

1. CPU
2. Memory
3. Network Performance
4. SSD vs HDD
5. IOPS and throughput

Prev: [scaling-mysql](scaling-mysql.md)
Next: [compliance-with-mysql](compliance-with-mysql.md)
