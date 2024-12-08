---
title: static-vs-dynamic-schemas
date created: Thursday, December 5th 2024, 10:38:12 pm
date modified: Thursday, December 5th 2024, 11:00:22 pm
---

Static schemas can enforce many things at compile time, whereas dynamic schemas don't. This means that static schemas are more strict but neither forwards or backwards compatible (you can't add a new field, remove an old field, change a field), but dynamic schemas can do any of those with the cost of having schema skew.
