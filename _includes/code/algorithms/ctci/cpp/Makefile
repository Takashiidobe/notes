all:
	make build -B && make -B run
build:
	g++-10 -std=c++20 -Wall -Wpedantic main.cc -o build/main
run:
	./build/main
clean:
	rm -rf build/*
