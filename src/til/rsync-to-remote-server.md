---
title: rsync-to-remote-server
---

to Remote Server\"

# Rsync to remote server

You may want to sync a remote with a your local computer. This happens a
lot when working on a VM.

To do so, you may write something like this:

```sh
set -gx REMOTE_HOME "/home/username"
set -gx REMOTE_HOST "username@hash.us-east-1.amazon.com"
set -gx LOCAL_DIR_TO_SYNC "$HOME/example_dir"

function start_sync
  while true
    sleep 2
    fd -H . | entr -d rsync -chavzP --stats --exclude-from="$HOME/.ignore" "$LOCAL_DIR_TO_SYNC" "$REMOTE_HOST:$REMOTE_HOME"
  end
end
```

This will start syncing your directory over to the remote host, on a 2
second loop.
