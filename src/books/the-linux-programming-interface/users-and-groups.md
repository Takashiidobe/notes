---
title: users-and-groups
---

# Users and Groups

Prev: [memory-allocation](memory-allocation.md) Next: [process-credentials](process-credentials.md)

## The Password File: `/etc/passwd`

The system password file, `etc/passwd` contains a line separated by colons for each user account on the system:

`mtk:x:1000:100:Michael Kerrisk:/home/mtk:/bin/bash`

The fields are:

- **Login name**: The username.
- **Encrypted password**: A 13-character encrypted password. If it is not 13 characters, logins are disabled. This field is `x` normally if logins are contained in the shadow password file.
- **User ID(UID)**: The numeric ID for this user. 0 is superuser.
- **Group ID(GID)**: The numeric ID of the first group the user is a part of.
- **Comment**: Text about the user.
- **Home directory**: the initial directory placed into after logging in.
- **Login Shell**: The program to which control is given after logging in.

## The Shadow Password File: `/etc/shadow`

Since many programs needed to read `/etc/passwd`, having encrypted password data there was a security risk. Thus, the shadow password file at `/etc/shadow` was created. Encrypted passwords are placed in `/etc/shadow`, and only privileged programs can read it.

## The Group File: `/etc/group`

The group file is in `/etc/group`. It might look like this:

```
users:x:100:
jambit:x:106:claus,felli,frank,harti,markus,martin,mtk,paul
```

The fields look like this:

- **Group name**: The name of the group
- **Encrypted password**: Normally `x` if there is a password, and placed in `/etc/gshadow`.
- **Group ID (GID)**: The numeric ID for the group. 0 is generally for root.
- **User list**: A comma separated list of members of this group.

## Retrieving User and Group Information

`getpwnam` and `getpwuid` retrieve records from the password file.

```c
#include <pwd.h>
struct passwd *getpwnam(const char *name);
struct passwd *getpwuid(uid_t uid); // Both return a pointer on success, or NULL on error; see main text for description of the “not found” case
```

Given a login name in `name`, `getpwnam` returns a pointer to a struct, `passwd` that looks like the following:

```c
struct passwd {
    char *pw_name; /* Login name (username) */
    char *pw_passwd; /* Encrypted password */
    uid_t pw_uid; /* User ID */
    gid_t pw_gid; /* Group ID */
    char *pw_gecos; /* Comment (user information) */
    char *pw_dir; /* Initial working (home) directory */
    char *pw_shell; /* Login shell */
};
```

`getpwuid` does the same, but with the numeric user id passed in.

Both functions return a statically allocated struct, which is overwritten on the next call to either `getpwnam`, `getpwuid` or `getpwnam`. Thus, the functions are not reentrant, and the reentrant versions (`getpwnam_r`, `getpwduid_r`, `pgetgrgid_r`) must be used.

### Retrieving Records from the group file

```c
#include <grp.h>
struct group *getgrnam(const char *name);
struct group *getgrgid(gid_t gid); // Both return a pointer on success, or NULL on error; see main text for description of the “not found” case
```

`getgrnam` and `getgrgid` are similar, but work for groups. They return this struct:

```c
struct group {
    char *gr_name; /* Group name */
    char *gr_passwd; /* Encrypted password (if not password shadowing) */
    gid_t gr_gid; /* Group ID */
    char **gr_mem; /* NULL-terminated array of pointers to names of members listed in /etc/group */
};
```

### Scanning all records in the password and group files

```c
#include <pwd.h>
struct passwd *getpwent(void); // Returns pointer on success, or NULL on end of stream or error
void setpwent(void);
void endpwent(void);
```

`getpwent` opens and returns records one by one from the password file, returning `NULL` when there are no more records.
`setpwent` can be used to set a password, and `endpwent` is used to close the file.

To loop through all the passwords, something like this can be used:

```c
struct passwd *pwd;
while ((pwd = getpwent()) != NULL) {
    printf("%-8s %5ld\n", pwd->pw_name, (long) pwd->pw_uid);
}
endpwent();
```

`getgrent`, `setgrent`, and `endgrent` are similar for the group id.

### Retrieving records from the shadow password file

Similar functions exist for the shadow password file.

```c
#include <shadow.h>
struct spwd *getspnam(const char *name); // Returns pointer on success, or NULL on not found or error
struct spwd *getspent(void); // Returns pointer on success, or NULL on end of stream or error
void setspent(void);
void endspent(void);
```

`getspnam` and `getspent` return pointers to a structure of type `spwd`.

```c
struct spwd {
    char *sp_namp; /* Login name (username) */
    char *sp_pwdp; /* Encrypted password */
    /* Remaining fields support "password aging", an optional
    feature that forces users to regularly change their
    passwords, so that even if an attacker manages to obtain
    a password, it will eventually cease to be usable. */
    long sp_lstchg; /* Time of last password change (days since 1 Jan 1970) */
    long sp_min; /* Min. number of days between password changes */
    long sp_max; /* Max. number of days before change required */
    long sp_warn; /* Number of days beforehand that user is warned of upcoming password expiration */
    long sp_inact; /* Number of days after expiration that account is considered inactive and locked */
    long sp_expire; /* Date when account expires (days since 1 Jan 1970) */
    unsigned long sp_flag; /* Reserved for future use */
};
```

## Password Encryption and User Authentication

To authenticate users in the unix way, passwords must be encrypted using `crypt` which uses the `DES` algorithm. `crypt` looks like this:

```c
#define _XOPEN_SOURCE
#include <unistd.h>
char *crypt(const char *key, const char *salt); // Returns pointer to statically allocated string containing encrypted password on success, or NULL on error
```

`crypt` takes a key, which is the password, up to 8 characters, and applies a 2 character salt to change the algorithm. The encrypted password starts with the original salt value as its first two characters.

To read a password from the terminal, `getpass` can be used:

```c
#define _BSD_SOURCE
#include <unistd.h>
char *getpass(const char *prompt); // Returns pointer to statically allocated input password string on success, or NULL on error
```

Prev: [memory-allocation](memory-allocation.md) Next: [process-credentials](process-credentials.md)
