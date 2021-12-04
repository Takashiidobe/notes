all:
	make build -B && make -B run
build:
	g++-10 -std=c++2a -Wall -Wpedantic -fconcepts main.cc -o build/main
run:
	./build/main
clean:
	rm -rf build/*
