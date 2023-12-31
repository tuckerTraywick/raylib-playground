OUTPUT_NAME := run
SRC_DIR := ./circle
BUILD_DIR := ./build
BIN_DIR := ./bin
LIBRARIES := -lraylib -lm

CFLAGS := -g -Wall -std=c17
CC := gcc

SRC_FILES := $(shell find $(SRC_DIR) -name '*.c')
OBJ_FILES := $(SRC_FILES:$(SRC_DIR)/%=$(BUILD_DIR)/%.o)

default: clean build

build: $(BIN_DIR)/$(OUTPUT_NAME)

$(BIN_DIR)/$(OUTPUT_NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(LDFLAGS) $? $(LIBRARIES) -o $@

$(OBJ_FILES): $(SRC_FILES)
	$(CC) $(CFLAGS) $? $(LIBRARIES) -c -o $@

.PHONY: run
run: default
	clear && $(MAKE) && $(BIN_DIR)/$(OUTPUT_NAME)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/* $(BIN_DIR)/*
