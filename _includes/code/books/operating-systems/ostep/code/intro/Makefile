
all: cpu mem threads io

CC=clang
FLAGS=-O3

clean:
	rm -f cpu mem threads io

cpu: cpu.c common.h
	$(CC) $(FLAGS) -o cpu cpu.c -Wall

mem: mem.c common.h
	$(CC) $(FLAGS) -o mem mem.c -Wall -no_pie

threads: threads.c common.h common_threads.h
	$(CC) $(FLAGS) -o threads threads.c -Wall -pthread

io: io.c common.h
	$(CC) $(FLAGS) -o io io.c -Wall

