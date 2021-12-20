CC = clang++
EXECUTABLE = poreq 
CFLAGS = -std=c++1z -Wall -g -O3 
SOURCES=$(wildcard ./src/*.cpp)
BUILD_DIR=./build
UNAME := $(shell uname)

all: $(SOURCES) | $(BUILD_DIR) 
	echo $(SOURCES)
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/$(EXECUTABLE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	$(RM) $(BUILD_DIR)/$(EXECUTABLE)

.PHONY: setup

setup:
	make clean
	make all 
