CC = gcc
CFLAGS = -I./inc
LDFLAGS = -lgpiod
BIN_DIR = ./bin
SRC_DIR = ./src

# Ensure bin directory exists
$(shell mkdir -p $(BIN_DIR))

# Main targets
all: $(BIN_DIR)/master

# Main executable
$(BIN_DIR)/master: $(BIN_DIR)/master.o $(BIN_DIR)/detection.o $(BIN_DIR)/identification.o
	$(CC) $^ $(LDFLAGS) -o $@

# Object file rules
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean