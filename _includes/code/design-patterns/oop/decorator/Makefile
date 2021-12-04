all:
	make decorator
decorator:
	make decorator-cc && make decorator-rs && make decorator-hs
decorator-hs:
	stack ghc decorator.hs && mv decorator build/decorator-hs && mv decorator.hi build/ && mv decorator.o build/ && ./build/decorator-hs
decorator-cc:
	clang++ -I/usr/local/include -L/usr/local/lib -lfmt decorator.cc -o build/decorator-cc && ./build/decorator-cc
decorator-rs:
	rustc decorator.rs -o build/decorator-rs && ./build/decorator-rs
