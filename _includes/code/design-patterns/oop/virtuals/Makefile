all:
	make template
template:
	make template-cc && make template-rs && make template-hs
template-hs:
	stack ghc template.hs && mv template build/template-hs && mv template.hi build/ && mv template.o build/ && ./build/template-hs
template-cc:
	clang++ -I/usr/local/include -L/usr/local/lib -lfmt template.cc -o build/template-cc && ./build/template-cc
template-rs:
	rustc template.rs -o build/template-rs && ./build/template-rs
