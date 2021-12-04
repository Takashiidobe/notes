all:
	make build -B && make -B run
build:
	g++-10 -std=c++20 -Wall -Wpedantic test.cc -o build/main
run:
	./build/main
clean:
	rm -rf build/*
