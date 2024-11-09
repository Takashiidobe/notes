---
title: Traceroute
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Friday, November 8th 2024, 10:24:17 pm
---
# Traceroute

Use traceroute to show the path of packets from your machine to a host.

```
$ traceroute takashiidobe.com
traceroute google.com
traceroute to google.com (142.250.72.110), 30 hops max, 60 byte packets
 1  _gateway (10.0.0.1)  5.504 ms  6.515 ms  6.494 ms
 2  96.120.68.73 (96.120.68.73)  25.260 ms  25.507 ms  25.489 ms
 3  24.124.215.205 (24.124.215.205)  24.302 ms  24.733 ms  24.716 ms
 4  96.110.117.121 (96.110.117.121)  25.400 ms  25.382 ms  36.183 ms
 5  * 96.110.117.93 (96.110.117.93)  41.650 ms *
 6  162.151.52.50 (162.151.52.50)  41.487 ms  17.243 ms  14.240 ms
 7  be-32031-cs03.newyork.ny.ibone.comcast.net (96.110.42.9)  20.609 ms be-32041-cs04.newyork.ny.ibone.comcast.net (96.110.42.13)  24.081 ms be-32031-cs03.newyork.ny.ibone.comcast.net (96.110.42.9)  24.044 ms
 8  be-3312-pe12.111eighthave.ny.ibone.comcast.net (96.110.34.42)  23.608 ms be-3112-pe12.111eighthave.ny.ibone.comcast.net (96.110.34.34)  23.668 ms be-3412-pe12.111eighthave.ny.ibone.comcast.net (96.110.34.46)  24.249 ms
 9  66.208.229.82 (66.208.229.82)  27.904 ms 96-87-11-70-static.hfc.comcastbusiness.net (96.87.11.70)  27.490 ms 66.208.229.82 (66.208.229.82)  27.873 ms
10  * * *
11  108.170.248.1 (108.170.248.1)  32.612 ms  32.284 ms 142.251.60.180 (142.251.60.180)  28.965 ms
12  108.170.248.84 (108.170.248.84)  30.934 ms 108.170.248.66 (108.170.248.66)  25.479 ms 142.251.65.93 (142.251.65.93)  25.460 ms
13  108.170.227.151 (108.170.227.151)  30.815 ms lga34s32-in-f14.1e100.net (142.250.72.110)  25.612 ms 142.251.69.59 (142.251.69.59)  25.636 ms
```

See `man traceroute` for more details.
