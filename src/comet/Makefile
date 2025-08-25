# Compiler settings
CC = gcc
CFLAGS = -I./detection/inc -I./I2C/inc -I./UART/inc
LDFLAGS = -lgpiod

# Directories
DETECTION_DIR = ./detection
I2C_DIR = ./I2C
UART_DIR = ./UART
BIN_DIR = ./bin

# Source files (excluding any master.c in subdirectories)
MASTER_SRC = master.c
DETECTION_SRC = $(DETECTION_DIR)/src/detection.c
I2C_SRC = $(I2C_DIR)/src/i2c_handler.c
UART_SRC = $(UART_DIR)/src/UART_handler.c

# Object files
DETECTION_OBJ = $(DETECTION_DIR)/bin/detection.o
I2C_OBJ = $(I2C_DIR)/bin/i2c_handler.o
UART_OBJ = $(UART_DIR)/bin/UART_handler.o
MASTER_OBJ = $(BIN_DIR)/master.o

# Final executable
TARGET = $(BIN_DIR)/master

all: $(TARGET)

$(TARGET): $(MASTER_OBJ) $(DETECTION_OBJ) $(I2C_OBJ) $(UART_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(MASTER_OBJ): $(MASTER_SRC)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(DETECTION_OBJ): $(DETECTION_SRC)
	@mkdir -p $(DETECTION_DIR)/bin
	$(CC) $(CFLAGS) -c $< -o $@

$(I2C_OBJ): $(I2C_SRC)
	@mkdir -p $(I2C_DIR)/bin
	$(CC) $(CFLAGS) -c $< -o $@

$(UART_OBJ): $(UART_SRC)
	@mkdir -p $(UART_DIR)/bin
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN_DIR)
	rm -f $(DETECTION_DIR)/bin/*.o
	rm -f $(I2C_DIR)/bin/*.o
	rm -f $(UART_DIR)/bin/*.o

.PHONY: all clean