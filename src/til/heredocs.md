---
title: heredocs
---

# Heredocs

Heredocs allow you to pass formatted strings in shell.

The syntax looks like the following:

```sh
[COMMAND] <<[-] 'DELIMITER'
  HERE-DOCUMENT
DELIMITER
```

Using a `-` causes all leading tab characters to be ignored. This allows you to use indentation when writing heredocs.

If you quote the delimiter, the shell will not substitute variables.

```sh
cat << EOF
The current working directory is: $PWD
You are logged in as: $(whoami)
EOF
```

The output might be:

```sh
The current working directory is: /home/takashiidobe
You are logged in as: takashiidobe
```

You can redirect the output too, with `<<` and `>`:

```sh
cat << EOF > file.txt
The current working directory is: $PWD
You are logged in as: $(whoami)
EOF
```

There heredoc can be piped as well:

```sh
cat <<'EOF' |  sed 's/l/e/g'
Hello
World
EOF
```

The output might look like:

```sh
Heeeo
Wored
```
