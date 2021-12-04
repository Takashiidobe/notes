CXX=g++-11
CXXFLAGS=--std=c++17 -O2 
WARNFLAGS=-Wall 
LDFLAGS=-fsanitize=address 
SRC=main.cc
TARGET=./build/main
INPUT=./input.txt

.PHONY: all run clean
all: run

$(TARGET): $(SRC) $(INPUT)
	$(CXX) $(CXXFLAGS) $(WARNFLAGS) $(LDFLAGS) $(SRC) -o $(TARGET) 
	
run: $(TARGET) 
	$(TARGET) && diff -u --ignore-space-change --strip-trailing-cr --ignore-blank-lines output.txt correct_output.txt	

clean:
	rm -f $(TARGET) 
