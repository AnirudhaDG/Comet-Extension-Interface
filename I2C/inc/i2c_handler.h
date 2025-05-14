#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>



int connect_i2c(uint8_t hex_array[], uint8_t *receive_data, const uint8_t key_size);