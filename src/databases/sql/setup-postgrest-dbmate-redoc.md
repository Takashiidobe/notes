---
title: setup-postgrest-dbmate-redoc
---

Postgrest Dbmate Redoc

# Setup Postgrest & Dbmate & Redoc

## Installation

Install all three dependencies:

```sh
brew install postgrest
```

```sh
brew install dbmate
```

```sh
yarn global add redoc-cli
```

## Dbmate

dbmate allows you to create migrations; you can use
`dbmate new ${migration}` to create a new migration, which will live in
`$PWD/db/migrations/${timestamp}_${migration}`.

you can apply the migration with `dbmate up` and remove it with
`dbmate down`.

Make sure to set your \$DATABASE_URL env variable to have sslmode
disabled in the URL, otherwise dbmate will not work in development.

## Postgrest

Postgrest is a binary that allows you to create REST endpoints and query
them with just the path to the database.

Example app.conf below:

```sh
db-uri = "postgres://postgres@localhost/movie_theater"
db-schema = "movie_theater"
db-anon-role = "movie_theater_anon"
```

This can be run with `postgrest app.conf`.

## Redoc

Redoc allows us to serve our documentation from our server root.

run `redoc-cli serve ${url || filename}` to serve the url or file as an
openapi schema.

run `redoc-cli bundle ${url || filename}` to bundle the url or file into
a single html file.
