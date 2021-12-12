---
title: "Optimizing Server Settings"
---

# Optimizing Server Settings

Prev: [operating-system-and-hardware-optimization](operating-system-and-hardware-optimization.md)
Next: [schema-design-and-management](schema-design-and-management.md)

Try to stick to the default settings: They're well understood.

## How MySQL's Configuration Works

MySQL's configuration is generally in `/etc/mysql/conf.cnf` and follows
the `ini` file format.

You can ask your mysql which configuration file it uses:

```sh
which mysqld
/usr/sbin/mysqld
/usr/sbin/mysqld --verbose --help | grep -A 1 'Default options'
Default options are read from the following files in the given order:
/etc/mysql/my.cnf ~/.my.cnf /usr/etc/my.cnf
```

Variables can be separated by underscores or dashes:

```sh
/usr/sbin/mysqld --auto-increment-offset=5
/usr/sbin/mysqld --auto_increment_offset=5
```

Variables can be changed while the server is running:

```sh
SET sort_buffer_size = <value>;
SET GLOBAL sort_buffer_size = <value>;
SET @@sort_buffer_size := <value>;
SET @@session.sort_buffer_size := <value>;
SET @@global.sort_buffer_size := <value>;
```

Variables that are set dynamically are lost when MySQL is shut down.

### Persisted System Variables

Variables that are changed dynamically can have unexpected side effects.

## What Not to Do

Don't tune by ratio.
Don't tune by using guided benchmarks.
Don't search the internet for configuration advice.
Don't believe the memory consumption formula. It's wrong.

## Creating a MySQL Configuration File

```ini
[mysqld]
# GENERAL
datadir                                  = /var/lib/mysql
socket                                   = /var/lib/mysql/mysql.sock
pid_file                                 = /var/lib/mysql/mysql.pid
user                                     = mysql
port                                     = 3306
# INNODB
innodb_buffer_pool_size                  = <value>
innodb_log_file_size                     = <value>
innodb_file_per_table                    = 1
innodb_flush_method                      = O_DIRECT
# LOGGING
log_error                                = /var/lib/mysql/mysql-error.log
log_slow_queries                         = /var/lib/mysql/mysql-slow.log
# OTHER
tmp_table_size                           = 32M
max_heap_table_size                      = 32M
max_connections                          = <value>
thread_cache_size                        = <value>
table_open_cache                         = <value>
open_files_limit                         = 65535
[client]
socket                                   = /var/lib/mysql/mysql.sock
port                                     = 3306
```

This is a minimalistic MySQL 8.0 conf file that the authors recommend.

## Configuring Memory Usage

`innodb_dedicated_server` will typically use 50%-75% of RAM. The rest
can be put into per-connection memory allocations and other things.

### Per-Connection Memory Needs

- High per-connection memory consumption can occur due to large
  temporary tables, or complex stored procedures.

### Reserving Memory for the OS

- Don't forget to allocate memory for the OS to let it work, like
  monitoring software, configuration management tooling, and scheduled
  jobs.

### The InnoDB Buffer Pool

The InnoDB buffer pool needs more memory than anything else, since it
caches indexes, row data, the adaptive hash index, the change buffer,
locks, and other internal structures.

Having a large buffer pool memory can slow startup and shutdown, due to
dirty pages needing to be written to disk. This can be modified with the
`innodb_max_dirty_pages_pct` variable.

When MySQL starts back up again, it has a cold cache, due to an empty
buffer pool cache. By default, `innodb_buffer_pool_dump_at_shutdown` and
`innodb_buffer_pool_load_at_startup` can make the buffer cache warmer.

### The Thread Cache

The thread cache holds threads that aren't associated with a connection
but ready to serve a new connection.

If there's a thread in the cache and a new connection is created, MySQL
takes a connection from the cache. When the connection is closed, MySQL
places the thread back into the cache if there's room, otherwise, it
destroys the thread.

The `thread_cache_size` variable specifies the number of threads MySQL
can keep in the cache.

A thread that's sleeping typically uses 256KB of memory, so it's not
very expensive to set this variable higher than you need. You can follow
`Threads_created` in the performance schema to tune this if you'd like.

## Configuring MySQL's I/O Behavior

### The InnoDB Transaction Log

InnoDB uses a transaction log to reduce the cost of committing
transactions. Instead of flushing the buffer pool to disk when each
transaction commits, it logs the transactions.

After appending to the transaction logs, InnoDB can replay the log and
recover transactions if the transactions weren't fully persisted to
disk.

InnoDB writes changes to datafiles in a circular fashion. When its log
is full, it starts committing transactions from the beginning and then
overwriting those transactions in the background.

The Logfile size is controlled by `innodb_log_file_size` and
`innodb_log_files_in_group` and are important for write performance.

### Log Buffer

When InnoDB changes data, it records its changes to its log buffer,
which it keeps in memory. InnoDB flushes the buffer to the logfiles on
disk when the buffer gets full.

#### How InnoDB flushes the log buffer

InnoDB flushes the log buffer by locking the buffer with a mutex,
flushing it up to a point, and then moving any remaining entries to the
front of the buffer.

The log buffer needs to be flushed to durable storage to ensure the
committed transactions are durable. This setting can be changed with
`innodb_flush_log_at_trx_commit`

The available settings are:

`0`

- Write the log buffer to the logfile and flush the logfile every second but do noth‐
  ing at transaction commit.

`1`

- Write the log buffer to the logfile and flush it to durable storage every time a
  transaction commits. This is the default (and safest) setting; it guarantees that
  you won't lose any committed transactions unless the disk or operating system
  "fakes" the flush operation.
`2`

- Write the log buffer to the logfile at every commit but don’t flush it. InnoDB
  schedules a flush once every second. The most important difference from the 0
  setting is that 2 won’t lose any transactions if the MySQL process crashes. If the
  entire server crashes or loses power, however, you can still lose transactions.

1 is generally the best default, since it doesn't lose transactions.

## The InnoDB tablespace

The InnoDB tablespace involves a virtual filesystem spanning one or many
files on disk, that holds tables. 

Prev: [operating-system-and-hardware-optimization](operating-system-and-hardware-optimization.md)
Next: [schema-design-and-management](schema-design-and-management.md)
