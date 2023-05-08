# You have 4GB physical memory, but you allocate an 8GB buffer. Is this possible? If so, how? How is the memory actually read as we traverse the memory?

Linux has 3 modes for handling memory allocations (overcommit):

- 0 (Heuristic overcommit handling): Obvious overcommits are refused. Root is allowed to allocate more memory in the mode. (This is the default)
- 1 (Always Overcommit): This mode allows as many memory allocations as possible. Useful for scientific applications that operate on sparse arrays.
- 2 (Don't Overcommit): Total Allocations cannot exceed swap + 50% of physical RAM. Overcommitted memory returns errors as appropriate.

Since processes require 8MB of RAM to run, and you'd have many processes + other processes that might map virtual memory to their address space, often a lot of RAM is unused at any given time. Due to this, if overcommit was disabled, far fewer applications would be able to run concurrently. Of course, overcommit does eventually cause paging errors, but at that point the computer is clearly overloaded.

You could `setrlimit` to set resources or use `cgroups`, if you'd like to guard against overcommitting.
