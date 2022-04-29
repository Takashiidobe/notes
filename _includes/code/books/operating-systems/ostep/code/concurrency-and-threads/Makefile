DEBUG_FLAGS = -g -O0
RELEASE_FLAGS = -O3 -march=native
BUILD_DIR = build
SRC_DIR = src
LIB_DIR = ../include

SRCS = $(shell find $(SRC_DIR)/ -type f -name "*.c")
LIBS = $(shell find $(LIB_DIR)/ -type f -name "*.c")
PROGS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%,$(SRCS))

all: $(PROGS)

build/%: $(SRC_DIR)/%.c $(LIBS)
	$(CC) $(RELEASE_FLAGS) -S $(LIBS) $< -o $@

clean:
	rm -r $(BUILD_DIR)

build:
	mkdir -p $(BUILD_DIR)

