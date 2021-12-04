all:
	make transport
transport:
	make transport-cc && make transport-rs && make transport-hs
transport-hs:
	stack ghc transport.hs && mv transport build/transport-hs && mv transport.hi build/ && mv transport.o build/ && ./build/transport-hs
transport-cc:
	clang++ -I/usr/local/include -L/usr/local/lib -lfmt transport.cc -o build/transport-cc && ./build/transport-cc
transport-rs:
	rustc transport.rs -o build/transport-rs && ./build/transport-rs
