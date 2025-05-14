#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>
#include <stdint.h>

int connect_uart(const char *portname, int baudrate, uint8_t hex_array[], const uint8_t key_size, uint8_t *output);

