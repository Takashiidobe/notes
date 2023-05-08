# What is NUMA?

NUMA stands for Non-uniform memory access, which provides separate memory for each processor in a computer, avoiding synchronization penalties when cores need to access the same memory. However, this can have performance penalties if different processors want to access the same information, as the hardware will need to synchronize data in the cache between two processors, but as long as that doesn't occur, there can be a linear speed up.
