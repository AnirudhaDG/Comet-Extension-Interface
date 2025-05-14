#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>
#include <stdint.h>

int connect_uart(const char *portname, int baudrate, uint8_t hex_array[]);

void process_uart_data(const uint8_t *read_buffer, int bytes_read);

int uart_read(int fd, char *buffer, size_t buffer_size);

int configure_uart(int fd, int baudrate);

int uart_write(int fd, const char *data, size_t length);
