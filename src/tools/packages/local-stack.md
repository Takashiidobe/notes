---
title: local-stack
---

Stack

# LocalStack

LocalStack is a python package that allows you to run a local instance
of popular AWS services in a docker container.

As with all docker packages, if you don\'t have docker on your computer,
install it.

Then, install `localstack` with `pip`.

```sh
pip3 install localstack
```

and run it.

use the ENV_VAR `SERVICES` with a comma separated list of services to
run only some services.

```sh
SERVICES=dynamodb localstack start
```
