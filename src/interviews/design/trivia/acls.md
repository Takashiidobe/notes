# ACLs

Access Control Lists (ACLs) allow you to specify permissions for users, groups, and other that aren't tied to the unix ownership scheme.

For a user: `setfacl -m "u:user:permissions" <file/dir>`
For a group: `setfacl -m "g:group:permissions" <file/dir>`
For others: `setfacl -m "other:permissions" <file/dir>`

ACLs can be seen with a `+` on the permissions:

```sh
$ ls -l /dev/audio

crw-rw----+ 1 root audio 14, 4 nov.   9 12:49 /dev/audio
```

This is commonly used by setting other's permissions to none, but adding permission for a specific user that isn't the current user.
