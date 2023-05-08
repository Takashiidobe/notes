# Process vs Thread

Processes have their own separate memory spaces and hold multiple threads.

Threads run in a process, share memory, and can be scheduled for execution. They have their own code, data, registers, and stack.

| Per process items           | Per thread items |
|-----------------------------|------------------|
| Address space               | Program counter  |
| Global variables            | Registers        |
| Open files                  | Stack            |
| Child processes             | State            |
| Pending alarms              |                  |
| Signals and signal handlers |                  |
| Accounting information      |                  |
