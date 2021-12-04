---
title: sync-with-android
---

With Android\"

# Sync With Android

To sync your phone with android, you might want to do something like
this:

```sh
scp -P 2222 (find $DIR_TO_SYNC/**/*.pdf -type f) "$IP_ADDRESS:/home/Documents"
```

The problem is, scp will always try to copy all files over. Obviously
that\'s not great if you have a lot of files.

You can try to sync only files updated in the last 7 days, but this
isn\'t exactly correct:

```sh
scp -P 2222 (find $DIR_TO_SYNC/**/*.pdf -type f -mtime -7) "$IP_ADDRESS:/home/Documents"
```

You\'d like to use rsync.

You can provide the command to execute with the `-e` flag:

```sh
rsync -rvz -e 'ssh -p 2222' --exclude-from="$HOME/.androidignore" --progress ~/$LOCAL_DIR "$IP_ADDRESS:/$LOCATION"
```

And now, files will be diffed properly.
