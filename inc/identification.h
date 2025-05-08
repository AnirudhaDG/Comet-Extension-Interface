#ifndef IDENTIFICATION_H
#define IDENTIFICATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>
#include <stdint.h>

int connect_uart(const char *portname, int baudrate);

int uart_read(int fd, char *buffer, size_t buffer_size);

int configure_uart(int fd, int baudrate);

int uart_write(int fd, const char *data, size_t length);

#endif