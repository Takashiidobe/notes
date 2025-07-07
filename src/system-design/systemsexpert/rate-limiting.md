---
title: Rate Limiting
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Sunday, July 6th 2025, 8:40:17 pm
---

# Rate Limiting

- Setting a threshold of allowing requests.

```{=html}
<!-- -->
```

    Client             Server             Database
    [    ]----------->[      ]---------->[        ]
    [    ]<-----------[      ]<----------[        ]

- Rate limiting protects DOS attacks.

- Rate limiting strategies:

  - By User:
  - By IP Address:
  - By Region:
  - By System:

You can use a small hash table of user -\> time accessed, and use that
to rate limit.

- Redis is a perfect use case for this, as you can uniquely identify
  each user.

- We can use redis for this, with a master slave architecture to
  remove the single point of failure.
