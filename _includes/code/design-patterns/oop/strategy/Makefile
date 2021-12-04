all:
	make strategy
strategy:
	make strategy-cc && make strategy-rs && make strategy-hs
strategy-hs:
	stack ghc strategy.hs && mv strategy build/strategy-hs && mv strategy.hi build/ && mv strategy.o build/ && ./build/strategy-hs
strategy-cc:
	clang++ -I/usr/local/include -L/usr/local/lib -lfmt strategy.cc -o build/strategy-cc && ./build/strategy-cc
strategy-rs:
	rustc strategy.rs -o build/strategy-rs && ./build/strategy-rs
