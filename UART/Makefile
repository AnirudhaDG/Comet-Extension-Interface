CC = gcc
CFLAGS = -I./inc -I../detection/inc
LDFLAGS = -lgpiod

SRC_DIR = ./src
INC_DIR = ./inc
BIN_DIR = ./bin
DETECTION_BIN = ../detection/bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRCS))
DETECTION_OBJ = $(DETECTION_BIN)/detection.o

# Targets
TARGET = $(BIN_DIR)/master

# Ensure directories exist
$(shell mkdir -p $(BIN_DIR) $(DETECTION_BIN))

# Main target
all: $(TARGET)

# Link main executable
$(TARGET): $(OBJS) $(DETECTION_OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

# Compile local sources
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# # Compile detection component
# $(DETECTION_OBJ): ../detection/src/detection.c
# 	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean