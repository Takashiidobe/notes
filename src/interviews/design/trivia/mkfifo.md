# Named pipes

A named pipe can be created with `mkfifo`, which creates a special file where one side can write to it and the other side can read from it without the use of an intermediate temporary file. This can reduce memory pressure.
