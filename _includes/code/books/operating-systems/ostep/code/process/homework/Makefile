DEBUG_FLAGS = -g -O0
RELEASE_FLAGS = -O3
BUILD_DIR = build
SRC_DIR = src
LIB_DIR = lib

SRCS = $(shell find $(SRC_DIR)/ -type f -name "*.c")
LIBS = $(shell find $(LIB_DIR)/ -type f -name "*.c")
PROGS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%,$(SRCS))

all: $(PROGS)

build/%: $(SRC_DIR)/%.c $(LIBS)
	$(CC) $(RELEASE_FLAGS) $(LIBS) $< -o $@$(VERSION)$(SUFFIX)

clean:
	rm -r $(BUILD_DIR)

build:
	mkdir -p $(BUILD_DIR)
