# How does the Python GIL work?

The Python's Global Interpreter Lock works by making it so each process of the python interpreter can only have one thread of bytecode run on it, making it so referencing counting was cheap (doesn't require taking a lock) since all code is linearizable.

This makes single-threaded programs fast, while multi-threaded programs are not. This also allowed C libraries to be ported as modules efficiently to python.

Python comes with a multiprocessing module to help spawn more processes of python in the background, or you can write c modules which occur outside of the GIL.
