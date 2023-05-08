# Processor Pinning

Processor pinning allows the binding of a process or thread to a CPU or range of CPUs, instructing the computer to run that task on only that CPU (or related ones). This can improve performance of a process/task, because caches and CPUs have a certain affinity, where during a context switch, they have to reload their state to disk and then rerun their task, which can take longer if the task hasn't run on that CPU already.
