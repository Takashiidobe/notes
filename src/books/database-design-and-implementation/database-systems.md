---
title: "Database Systems"
---

# Database Systems

Next: [jdbc](jdbc.md)

Database systems contains records persisted on a computer, normally in files.

Using a plain text encoding would be inefficient, so records are generally stored in binary. As well, storing it in one large text file would make editing inefficient. The larger a file is, the slower it is to update, due to seeking problems. Also, it isn't possible to efficiently edit a file at the beginning or middle of a file.

Multiple users should also be able to access data and modify it concurrently. The database system must allow for correct data to be persisted with low latency. However, concurrency should be limited when required, such as when an item must be atomically guarded. As well, "undoable" operations should not be shown to other users until the operation is successful. If the operation fails, it should be rolled back.

Typical access times are around 60 nanoseconds for RAM, 60 microseconds for flash, and 6ms for disk. RAM is about 1000x faster than flash memory, and 1 million times faster than disk.

> In other words, a database system is faced with the following conundrum: It must manage more data than main memory systems, using slower devices, with multiple people fighting over access to the data, and make it completely recoverable, all the while maintaining a reasonable response time.

A database must also provide a good user interface. The most common language to query data is SQL.

This book outlines the design of "SimpleDB", a small relational database. It implements a tiny subset of standard SQL and imposes restrictions on it to make implementation easier.

## Exercises

### Conceptual Exercises

1.1. Suppose that an organization needs to manage a relatively small number of
shared records (say, 100 or so).

(a) Would it make sense to use a commercial database system to manage these
records?

Probably not, since they have a lot of features more useful for large amounts of data.

(b) What features of a database system would not be required?

Probably not joins, since there are so few records. Assuming the data is homogeneous, some kind of spreadsheet software might be better.

(c) Would it be reasonable to use a spreadsheet to store these records? What are
the potential problems?

Spreadsheets are probably fine, but if two users want to make concurrent updates, they would have to resolve conflicts themselves (say they both update the same record). Most of the time, it should be fine, but without version control, updates could be lost, causing problems to other users.

1.2. Suppose you want to store a large amount of personal data in a database. What
features of a database system wouldn't you need?

I would be the only reader and writer, thus, I would not need concurrent access to data in the database, so MVCC and other features would be useless.

1.3. Consider some data that you typically manage without a database system (such
as a shopping list, address book, checking account info, etc.).

(a) How large would the data have to get before you would break down and
store it in a database system?

Extremely large, pushing into the hundreds of GBs, since even large GB files are easily readable and updatable on modern hardware. As well, the data would probably need to be relational in nature, but even then, statistical software with dataframes might be simpler.

(b) What changes to how you use the data would make it worthwhile to use a
database system?

If I wanted faster concurrent updates as well as an easier way to specify joins.

1.4. If you know how to use a version control system (such as Git or Subversion),
compare its features to those of a database system.

(a) Does a version control system have a concept of a record?

Yes - files are like records.

(b) How does check-in/checkout correspond to database concurrency control?

Staging code is like starting a transaction.
Checking in code is like committing a transaction, just manually.
Checking out code is like reading from the dataset.

(c) How does a user perform a commit? How does a user undo uncommitted
changes?

A user would commit changes by merging them into a different branch. They can also be undone by removing said changes.

(d) Many version control systems save updates in difference files, which are
small files that describe how to transform the previous version of the file
into the new one. If a user needs to see the current version of the file, the
system starts with the original file and applies all of the difference files to
it. How well does this implementation strategy satisfy the needs of a
database system?

These diffs are useful for version control, because it means a user can go back in time to any point in the repository. For a database, that level of granularity might not be as useful.

### Project-Based Exercises

1.5. Investigate whether your school administration or company uses a database
system. If so:
(a) What employees explicitly use the database system in their job?
(As opposed to those employees who run "canned" programs that use the
database without their knowledge.) What do they use it for?

Most of the developers can use the database directly, and some of the ops people can use UIs that connect to the database (canned). They use it to change some settings for users. The developers can do anything with the data, which can be problematic at times.

(b) When a user needs to do something new with the data, does the user write
his own query, or does someone else do it?

The user can only run specific jobs, which are written by the developers, to prevent malformed data from getting into the database.

1.6. Install and run the Derby and SimpleDB servers.
(a) Run the ij and SimpleIJ programs from the server machine.
(b) If you have access to a second machine, modify the demo clients and run
them remotely from that machine as well.

N/A

Next: [jdbc](jdbc.md)
