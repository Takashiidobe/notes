---
title: "Backup and Recovery"
---

# Backup and Recovery

Prev: [replication](replication.md)
Next: [scaling-mysql](scaling-mysql.md)

Backups are important: think of the following:

1. Security (access to the backups, privileges to restore data,
   encryption)
2. Where to store the backups (different disk, server, or offsite)
3. Retention policies
4. Storage solutions
5. Storage formats
6. Monitoring backups
7. Backup capabilities built into storage layers

## Why Backups?

1. Disaster recovery
2. People changing their minds
3. Auditing
4. Testing

Most cloud providers don't provide backups of servers at all.

## Defining Recovery Requirements

Think about the following:

1. How much data can you lose without serious consequences?
2. How fast does recovery have to be? How much availability loss will
   your customers tolerate?
3. What do you need to recover? A table? A database? A server?

## Designing a MySQL Backup Solution

Backups have lots of criteria. Snapshot-based backups like Percona
XtraBackup and MySQL Enterprise Backup are the best.

### Online or Offline Backups?

If you can get away with it, shutting down the server to writes makes
backups easy.

If your application has less traffic during some times, this is a good
time to run backups while online.

### Logical or Raw Backups?

Logical backups (dumps) contains data in a format that MySQL can
understand, like SQL.

Raw files are files as they exist on disk.

#### Logical Backups

Logical Backups are normal sql files. That means they can be independent
of storage engine, and helps avoid data corruption.

There are some cons:

- The server spends more CPU time generating them
- Dumping and restoring data can sometimes be non-deterministic
- Restoring from a logical backup requires MySQL to load and interpret
  statements, which is very slow.

#### Raw backups

- Raw backups are generally cheaper to generate
- Faster to backup

But have some cons:

- Are often far larger than logical backups
- Raw backups might run into architecture specific problems.

Raw backups are generally easier and more efficient, but should not be
relied upon for legal requirements.

You should try to dump in both formats.

### What to Back Up

You need to backup stuff that's not just in tables:

- Binlogs, and InnoDB transaction logs
- Code (like triggers and stored procedures)
- Server configuration
- Operating system files, like cron jobs and administrative scripts

### Incremental Backups

Incremental backups are good in the case you can't backup the whole
database. First, take a whole snapshot, then incrementally take snapshot
changes from that time.

### Replication

When you make a backup from a replica, GTID's are recommended. This
avoids having to save all the information about the replica.

## Managing and Backing Up Binary Logs

MySQL will fill up your disk with binary logs. You'll need to decide on
a log-based expiration policy to keep MySQL from filling your disk with
binary logs.

MySQL can purge binlogs automatically with `binlog_expire_logs_seconds`.

## Backup and Recovery Tools

1. MySQL Enterprise Tools (Oracle provided)
2. Percona XtraBackup (open sourcing and free)
3. mydumper (multi-threaded backups)
4. mysqldump (comes with MySQL)

### Logical SQL Backups

Mysqldump creates logical dumps by default:

You can run `mysqldump` like so:

```sql
 mysqldump test t1
-- [Version and host comments]
/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
-- [More version-specific comments to save options for restore]
--
-- Table structure for table `t1`
--
DROP TABLE IF EXISTS `t1`;
/*!40101 SET @saved_cs_client = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `t1` (
 `a` int NOT NULL,
 PRIMARY KEY (`a`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;
--
-- Dumping data for table `t1`
--
LOCK TABLES `t1` WRITE;
/*!40000 ALTER TABLE `t1` DISABLE KEYS */;
INSERT INTO `t1` VALUES (1);
/*!40000 ALTER TABLE `t1` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
-- [More option restoration]
```

There are some problems with logical backups:

1. Schema and data stored together.
2. Huge SQL Statements
3. A single huge file
4. Logical backups are expensive

### Filesystem Snapshots

Filesystem snapshots are a good way to make online backups. ZFS, LVM,
SAN, and other filesystems can take snapshots for use.

#### How LVM snapshots work

LVM uses copy-on-write to create a snapshot. It's a logical copy of an
entire volume at an instant in time. This works like MVCC, except only
keeping one old version of the data.

#### Prerequisites and configuration

To get a consistent copy of all the files you want to backup:

- All InnoDB files must be on a single logical volume.
- If you need to backup table definitions, the MySQL data directory must
  be on the same Logical volume.
- The volume group must have enough free space to create the snapshot.

LVM has the concept of a volume group, which contains one or more
logical volumes. You can query this with `vgs`.

```sh
$ vgs
 VG #PV #LV #SN Attr VSize VFree
 vg 1 4 0 wz--n- 534.18G 249.18G
```

The `lvs` command shows the logical volumes on the system.

```sh
lvs
 LV VG Attr LSize Origin Snap% Move Log Copy%
 home vg -wi-ao 40.00G
 mysql vg -wi-ao 225.00G
 tmp vg -wi-ao 10.00G
 var vg -wi-ao 10.00G
```

The MySQL volume has 225GB of space, and it is named `/dev/vg/mysql`.

To create, mount, and remove an LVM snapshot:

You can use the `lvcreate` command to create a logical backup,
`backup_mysql`.

```sh
lvcreate --size 16G --snapshot --name backup_mysql /dev/vg/mysql
 Logical volume "backup_mysql" created
```

You can watch its status with nagios:

```sh
watch 'lvs | grep backup'
```

#### Lock-free InnoDB backups with LVM snapshots

To take a backup on MySQL 8+, while MySQL is running, take a snapshot,
mount the snapshot, and then copy the files to your backup location.

Calculate how much data your server writes by use `vmstat` or `iostat`.

Assume it takes an hour to copy the snapshot to another server. You will
need 1/2 _ 10MB _ 3600 or about 18GB of space for the snapshot.

### Percona XtraBackup

Percona XtraBackup is a popular solution for backing up MySQL.

#### How XtraBackup works

It can be used like so:

```sh
xtrabackup --backup --target-dir=/backups/

xtrabackup version 8.0.25-17 based on MySQL server 8.0.25 Linux (x86_64)
(revision id: d27028b)
Using server version 8.0.25-15
210821 17:01:40 Executing LOCK TABLES FOR BACKUP...
```

#### Example usage

##### Basic Backup to directory

```sh
xtrabackup --backup --target-dir=/backups/
```

##### Streaming backup

This command does streaming backups to stdout.

```sh
xtrabackup --backup --stream=xbstream > /backups/backup.xbstream
```

You could add the timestamp too:

```sh
xtrabackup --backup --stream=xbstream > /backups/backup-$(date +%F).xbstream
```

##### Backup with compression

Or with compression and streaming

```sh
xtrabackup --backup --compress --stream=xbstream > /backups/backup-
compressed.xbstream
```

##### Backup with encryption

You can also encrypt your backups.

```sh
xtrabackup --backup --encrypt=AES256 --encrypt-key-
file=/safe/key/location/encrypt.key --stream=xbstream > /backups/backup-
encrypted.xbstream
```

##### Other important flags

You can look at the `--parallel` and `-compress-threads` options, or
`--rsync` to optimize the file-copy process.

## Recovering from a Backup

To recover from a backup:

1. Stop the MySQL server.
2. Take notes on the server’s configuration and file permissions.
3. Move the data from the backup into the MySQL data directory.
4. Make configuration changes.
5. Change file permissions.
6. Restart the server with limited access, and wait for it to start fully.
7. Reload logical backup files.
8. Examine and replay binary logs.
9. Verify what you've restored.
10. Restart the server with full access.

Make sure that MySQL is inaccessible to everything but the recovery
process: start MySQL with the `--skip-networking` and
`--socket=/tmp/mysql_recover.sock` options.

### Restoring Logical Backups

If you have a logical backup, you can pass it to mysql directly:

```sh
mysql < sakila-backup.sql
```

If you compressed the backup, you can decompress and load in a single
operation:

```sh
gunzip -c sakila-backup.sql.gz | mysql
```

Or for a single table:

```sh
grep 'INSERT INTO `actor`' sakila-backup.sql | mysql sakila
```

Or if the file is compressed:

```sh
gunzip -c sakila-backup.sql.gz | grep 'INSERT INTO `actor`'| mysql sakila
```

Try to backup into tables and data to avoid having to `sed` a huge dump
file.

### Restoring Raw Files from Snapshot

To restore raw files, shut down MySQL, copy or move the files into
place, and then restart.

### Restoring with Percona XtraBackup

If you used a streaming backup, unpack the `xbstream` file.

```sh
xbstream -x < backup.xbstream
```

For a compressed file, pass `--decompress` and for an encrypted file,
pass `--decrypt` with `--encrypt-key-file`.

```sh
xbstream -x --decompress < backup-compressed.xbstream
```

```sh
xbstream -x --decrypt --encrypt-key-file=/safe/key/location/encrypt.key
 < backup-encrypted.xbstream
```

Once complete, you can prepare the files:

```sh
xtrabackup --prepare --target-dir=/restore
```

And then restore:

```sh
xtrabackup --move-back --target-dir=/restore
```

### Starting MySQL After Restoring Raw Files

Now that you've restored the backup, pay attention to unix permissions,
otherwise MySQL might not start.

Also, watch the MySQL error log while the server starts.

```sh
tail -f /var/log/mysql/mysql.err
```

You should run `SHOW TABLE STATUS` in each database, and check the error
log in newer versions.

Prev: [replication](replication.md)
Next: [scaling-mysql](scaling-mysql.md)
