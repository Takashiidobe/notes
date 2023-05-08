# Fork

Fork works by duplicating the process. The process is duplicated into two (parent and child) unless it fails (returns -1).
The parent fork returns 0, and the child fork returns > 1. `getpid()` can be used to find the child, and the child can get the parent's pid with `getppid()`.
Fork also copies the entire process space with Copy on Write semantics, so as long as the child process nor the parent process write to their pages, they get fine performance.
