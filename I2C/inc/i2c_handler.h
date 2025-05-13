#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>


int i2c_init();

int i2c_send(const unsigned char* data, int length);

int i2c_receive(unsigned char* buffer, int length);

void i2c_close();
