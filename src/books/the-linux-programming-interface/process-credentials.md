---
title: process-credentials
---

# Process Credentials

Prev: [users-and-groups](users-and-groups.md) Next: [times-and-dates](times-and-dates.md)

Every process has credentials:

- real user ID and group ID
- effective user ID and group ID
- saved set user ID and saved set group ID
- file system user ID and group ID
- supplementary group IDs

## Real User ID and Real Group ID

The Real User ID and Real Group ID identify the user and group to which the process belongs.

## Effective User ID and effective Group ID

The effective user ID and group ID are used to determine the permissions granted to a process when it tries to perform various operations.
A process with an effective user ID of 0 has all the privileges of the super user.
Normally real and effective ids are the same, but they can be different due to system calls.

## Set-User-ID and Set-Group-ID Programs

A Set-User-ID program allows a process to gain privileges it was not originally granted. This is done by setting the process' effective user ID to the same value as the user ID of the executable file. A Set-Group-ID does the same for the effective group id.

When an executable is allowed to be executable by a user (`chmod +x ./executable`) and then run, the kernel sets the effective user ID of the process to be the same as the user ID of the executable file. This is the same for the group ID.

Some Set-User-ID and Set-Group-ID programs are `sudo` or `su`. These programs become useless if they are not owned by the root user, because anybody could call them to gain access to anything on the system.

## Saved Set-User-ID and Saved Set-Group-ID

The saved set-user-ID and saved set-group-ID are designed for set-user-ID and set-group-ID programs. Imagine if a real user with a user id of `1000` runs a program with set-user-ID of `0`.

After running, the user IDs of the process look like the following:

`real=1000 effective=0 saved=0`.

## File-System User ID and File-System Group ID

On Linux, there are also File-System User IDs and File-System Group IDs. This is a historical artifact of the NFS. Two additional system calls, `setfsuid` and `setfsgid` are provided to set these ids as well.

## Supplementary Group IDs

Supplementary group IDs are a set of additional groups to which a process belongs, inheriting IDs from its parent.

## Retrieving and Modifying Process Credentials

Linux provides system calls for modifying process credentials, and provides the constants `CAP_SETUID` and `CAP_SETGID` to allow a process to make changes to its user ids and group ids.

### Retrieving real and effective ids

To retrieve real and effective ids, the following calls are provided:

```c
#include <unistd.h>
uid_t getuid(void); // Returns real user ID of calling process
uid_t geteuid(void); // Returns effective user ID of calling process
gid_t getgid(void); // Returns real group ID of calling process
gid_t getegid(void); // Returns effective group ID of calling process
```

### Modifying effective ids

```c
#include <unistd.h>
int setuid(uid_t uid);
int setgid(gid_t gid); // Both return 0 on success, or –1 on error
```

There are a few rules:

1. When an unprivileged process calls `setuid`, only the effective user ID of the process is changed. It can only be changed to the real user ID or the set-user-ID. If not, the error `EPERM` is raised. This is only useful for unprivileged users executing a set-user-ID program.
2. When a privileged process calls `setuid`, it changes its user id to the given value, but then loses the ability to call `setuid` again to change its user id, because it is no longer privileged. This can be avoided by using `seteuid` and `setreuid`.

To set effective group ids, the following exists:

```c
#include <unistd.h>
int seteuid(uid_t euid);
int setegid(gid_t egid);
```

Again the same caveat:

1. An unprivileged process can change an effective ID only to the same value as the corresponding real or saved set ID.
2. A privileged process can change an effective ID to any value. It stops being privileged afterwards.

### Modifying real and effective IDs

```c
#include <unistd.h>
int setreuid(uid_t ruid, uid_t euid);
int setregid(gid_t rgid, gid_t egid); // Both return 0 on success, or –1 on error
```

The functions follow the same rules.

### Retrieving real, effective and saved set IDs

```c
#define _GNU_SOURCE
#include <unistd.h>
int getresuid(uid_t *ruid, uid_t *euid, uid_t *suid);
int getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid); // Both return 0 on success, or –1 on error
```

### Modifying real, effective, and saved set IDs

```c
#define _GNU_SOURCE
#include <unistd.h>
int setresuid(uid_t ruid, uid_t euid, uid_t suid);
int setresgid(gid_t rgid, gid_t egid, gid_t sgid); // Both return 0 on success, or –1 on error
```

### Retrieving and Modifying File-System IDs

```c
#include <sys/fsuid.h>
int setfsuid(uid_t fsuid); // Always returns the previous file-system user ID
int setfsgid(gid_t fsgid); // Always returns the previous file-system group ID
```

### Retrieving and Modifying Supplementary Group IDs

To get group IDs:

```c
#include <unistd.h>
int getgroups(int gidsetsize, gid_t grouplist[]); // Returns number of group IDs placed in grouplist on success, or –1 on error
```

To modify supplementary group IDs:

```c
#define _BSD_SOURCE
#include <grp.h>
int setgroups(size_t gidsetsize, const gid_t *grouplist);
int initgroups(const char *user, gid_t group); // Both return 0 on success, or –1 on error
```

Prev: [users-and-groups](users-and-groups.md) Next: [times-and-dates](times-and-dates.md)
