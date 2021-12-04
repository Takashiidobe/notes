---
title: push-to-multiple-remotes-at-the-same-time
---

To Multiple Remotes At The Same Time

# Push to Multiple Remotes at the Same Time

Let\'s say you have multiple git repos that you\'d like to keep in sync.

Normally you might do something like this:

```sh
git remote add github github.com:user/repo.git
git remote add bitbucket bitbucket.org:user/repo.git
```

And then you need to push to both of them to keep them in sync:

```sh
git push github master
git push bitbucket master
```

You can make a shell script to wrap pushes, but that\'s tedious.
Instead, set the remote push URLs like so:

```sh
git remote set-url --add --push origin github.com:user/repo.git
git remote set-url --add --push origin bitbucket.org:user/repo.git
```

Make sure that you see both repos pointed to as origin by running:

```sh
git remote show origin
```

Next time you push, you should see both remotes properly synced.
