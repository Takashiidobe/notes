# Locking Selects

Postgres and other RDBMSes support `SELECT FOR SHARE` and `SELECT FOR
UPDATE`, which allow you to lock a row or set of rows in a table with a
lock.

- `FOR SHARE` locks a row for reads in shared mode, so other
sessions can read the rows, but cannot modify them until the current
transaction commits. As well, if the rows were updated by a different
transaction, then `FOR SHARE` waits until the other transactions have
committed before comitting.

- `FOR UPDATE` locks a row for writes in exclusive mode, so other
  transactions are blocked from reading or updating the rows,
  or doing `SELECT FOR SHARE` or `SELECT FOR UPDATE`.

These can be enhanced with `NOWAIT` and `SKIP LOCKED`.

- `NOWAIT` means that any rows with a `SELECT FOR SHARE` or `SELECT FOR
UPDATE` never wait for any locked rows and returns an error if a
requested row is locked.

- `SKIP LOCKED` never waits to acquire a locked row, and simply
  continues on without the locked rows.
