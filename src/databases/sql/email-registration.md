---
title: email-registration
---

Registration

# Email Registration

Let\'s say you want to verify your users email before you allow them to
sign up for your application. There are two paths from there: either the
user verifies their account, or they don\'t. We\'ll eventually want to
cull unregistered users, but we don\'t want to do it so frequently
(unless your application is REALLY popular).

We\'ll build two tables: One that stores registrations, and one that
stores users.

Let\'s say that we have a table for registrations like so:

Registration Table:

id email createdAt verified userId

---

1 example.email.com NOW() TRUE 1
2 example.email.com NOW() FALSE NULL

Let\'s say that we have a table for registered users like so:

Users Table:

id email password createdAt

---

1 example.email.com hashedPassword NOW()

When we receive a registration, we check if the user exists in the Users
table. If so, we tell them that you\'ve already registered. If we don\'t
find the user in the User\'s table, we have to check the registration
table where verified is set to false. If we find a match, we check to
see if the createdAt is longer than a day, if so, we allow them to
create an account, update the createdAt, and send them an email.

If they click the button in their email, we update their row to
verified, create a row in the users table, and insert that id into the
userId column in the registration table.

This has two queries through two tables, so it isn\'t the most
efficient, but this can be made more efficient by culling through the
second table every once in a while. Otherwise, we can combine them both
into one table, so all we have to face is a one table scan where
everything is in one table. It\'s up to you.
