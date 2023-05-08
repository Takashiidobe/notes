# How do you run multiple processes on a computer?

The OS allows many processes to run on a computer at once. To allow processes fair time at using the scheduler, the scheduler gives them all a timeslice and calls this an epoch.

When booting the OS, after the kernel has set up its code, the root user starts its init system (generally systemd) which can start arbitrary programs as arbitrary users (it forks from the root user, and then uses `setuid()` to allow it to become a different user process).

You can `fork()` and `execve()` to run different processes on a computer in Linux.
