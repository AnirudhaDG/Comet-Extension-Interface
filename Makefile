# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I./inc
LDFLAGS = -lgpiod

# Directory structure
SRC_DIR = ./src
INC_DIR = ./inc
BIN_DIR = ./bin

# Ensure bin directory exists
$(shell mkdir -p $(BIN_DIR))

# Individual targets
DETECTION = $(BIN_DIR)/detection
IDENTIFICATION = $(BIN_DIR)/identification
MASTER = $(BIN_DIR)/master

# Default target (builds everything)
all: $(MASTER) $(DETECTION) $(IDENTIFICATION)

# Master program (links all objects)
$(MASTER): $(BIN_DIR)/master.o $(BIN_DIR)/detection.o $(BIN_DIR)/identification.o
	$(CC) $^ $(LDFLAGS) -o $@

# Individual compilation targets
detection: $(DETECTION)
identification: $(IDENTIFICATION)
master: $(MASTER)

# Detection binary
$(DETECTION): $(SRC_DIR)/detection.c
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

# Identification binary
$(IDENTIFICATION): $(SRC_DIR)/identification.c
	$(CC) $(CFLAGS) $< -o $@

# Clean
clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean detection identification master