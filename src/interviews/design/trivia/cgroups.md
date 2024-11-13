---
title: Cgroups
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Tuesday, November 12th 2024, 7:09:14 pm
---

# Cgroups

Control Groups (`cgroups`) are a feature to limit, and isolate the resource usage of a collection of processes in a group.

`cgcreate`, `cgexec`, `cgclassify` are the ways to manipulate a cgroup.

These are hierarchical, so they can inherit limits from a parent group, and can limit memory usage with `memory` controllers, or limit CPU usage with `cpuacct`.
