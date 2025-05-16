#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include "i2c_handler.h"

#define I2C_DEVICE "/dev/i2c-2"
#define DEVICE_ADDRESS 0x16

int i2c_fd = -1;

int i2c_init() {
    if ((i2c_fd = open(I2C_DEVICE, O_RDWR)) < 0) {
        perror("Failed to open the i2c bus");
        return -1;
    }
    
    if (ioctl(i2c_fd, I2C_SLAVE, DEVICE_ADDRESS) < 0) {
        perror("Failed to acquire bus access and/or talk to slave");
        close(i2c_fd);
        i2c_fd = -1;
        return -1;
    }
    
    return i2c_fd;
}

int i2c_send(const unsigned char* data, int length) 
{
    if(write(i2c_fd, data, length) != length)
    {
        perror("Failed to write message");
        return -1;
    }
    return 0;
}

int i2c_receive(unsigned char* buffer, int length) {

    if (read(i2c_fd, buffer, length) != length) {
        perror("Failed to read from the i2c device");
        return -1;
    }
    // else{
    //     printf("Received: '%s'\n", buffer);
    // }
    return 0;
}

void i2c_close() {
    if (i2c_fd >= 0) {
        close(i2c_fd);
        i2c_fd = -1;
    }
}

int process_i2c_data(char received_data[], const uint8_t key_size)
{
    if (received_data[0] == 0xaa && received_data[key_size - 1] == 0xff)
    {
        printf("Packet Validated\n");
        return 1;
    }
    else
    {
        printf("Invalid Data\n");
        return -1;
    }
}

int connect_i2c(uint8_t hex_array[], uint8_t *receive_data, const uint8_t key_size)
{
    int i2c_fd = i2c_init();

    if (i2c_fd < 0) {
        return 0;
    }
    
    printf("Attempting connection over I2C\n");
    if (i2c_send(hex_array, key_size) > 0) 
    {
        i2c_close();
        return 1;
    }
    // else {return 0;}

    usleep(100000);

    printf("Receiving data from I2C\n");
    if (i2c_receive(receive_data, key_size)) {
        i2c_close();
        return 1;
    }
    else{return 0;}

    usleep(100000);

    i2c_close(i2c_fd);

    if (process_i2c_data(receive_data, key_size) > 0)
    {
        return 1;
    }
    else{
        return -1;
    }
}
