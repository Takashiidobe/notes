---
title: load-testing-with-bombardier
---

Testing With Bombardier

# Load Testing with Bombardier

You can load test with bombardier, using something like this:

`bombardier -c 125 -n 10000 http://localhost:3000/theaters -f body.json -m POST -H 'Content-Type: application/json'`
