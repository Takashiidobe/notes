---
title: monotonic-time
---

Time

# Monotonic Time

- Use Erlang\'s monotonic_time for timing, since it isn\'t affected by
  OS clock changes.

> `System.monotonic_time/1` Returns the current monotonic time in the
> given time unit. The time is monotonically increasing and starts in an
> unspecified point in time.

```ex
start_time = System.monotonic_time(:microseconds)

# do something

end_time = System.monotonic_time(:microseconds)

duration_in_microseconds = end_time - start_time
```
