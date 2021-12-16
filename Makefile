CC = clang++
TARGET_FILE = poreq 
CFLAGS = -std=c++11 -Wall -g 
SOURCES=$(wildcard ./src/*.cpp)
BUILD_DIR=./build

all: $(SOURCES)
	echo "the source files are ..."
	echo $(SOURCES)
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/$(TARGET_FILE)

clean:
	$(RM) $(BUILD_DIR)/$(TARGET_FILE)

.PHONY: setup
setup:
	mkdir outputs
	make clean
	make all 


