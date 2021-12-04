---
title: polling-and-streaming
---

And Streaming

# Polling and Streaming

               Polling
    Client                    Server
    [    ]--Every x seconds-->[    ]
    [    ]<-------------------[    ]

               Streaming
               Continuous
    [    ]<-------data--------[    ]

- Polling is heavy, and non-responsive, since it only updates every
  `x` seconds.

- Streaming inverts this responsibility, because the server pushes
  data to the client.

- Instantaneous experience -\> Streaming

- Polling might be better when there are less updates.

Prev:
\[peer-to-peer-networks](peer-to-peer-networks.md)
Next: \[configuration](configuration.md)
