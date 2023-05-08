# Link Time Optimization (LTO)

Link Time optimization allows for optimizing the whole program, instead of just at translation units. This can make the binary smaller or faster (at the cost of the other).
There are two rough types in clang, thin and fat.

Thin has fewer optimizations + less compile time + smaller binary bloat.
Fat has more optimizations + more compile time + more binary bloat.

There are some problems with LTO, where it might look at the entire linked set of object files and delete code that is actually necessary for the program to function, causing a runtime error where without LTO the program worked properly.
