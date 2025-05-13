#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#define I2C_DEVICE "/dev/i2c-2"
#define DEVICE_ADDRESS 0x16

int i2c_fd = -1;

uint8_t hex_array[] = {0xAA, 0x55, 0x01, 0xFF, 0x00, 0x69, 0x88, 0x96};

int i2c_init() {
    // Open the I2C bus
    if ((i2c_fd = open(I2C_DEVICE, O_RDWR)) < 0) {
        perror("Failed to open the i2c bus");
        return -1;
    }
    
    // Set the I2C slave address
    if (ioctl(i2c_fd, I2C_SLAVE, DEVICE_ADDRESS) < 0) {
        perror("Failed to acquire bus access and/or talk to slave");
        close(i2c_fd);
        i2c_fd = -1;
        return -1;
    }
    
    return 0;
}

int i2c_send(const unsigned char* data, int length) 
{
    if(write(i2c_fd, data, 8) != 8)
    {
        perror("Failed to write message");
        return -1;
    }
    // for (int i = 0; i < length; i++)
    // {
    //     if (write(i2c_fd, &data[i], 1) != 1) {
    //         perror("Failed to write to the i2c device");
    //         return -1;
    //     }            
    // }
    return 0;
}

int i2c_receive(unsigned char* buffer, int length) {

    if (read(i2c_fd, buffer, length) != length) {
        perror("Failed to read from the i2c device");
        return -1;
    }
    else{
        printf("Received: '%s'\n", buffer);
    }
    return 0;
}

void i2c_close() {
    if (i2c_fd >= 0) {
        close(i2c_fd);
        i2c_fd = -1;
    }
}

int main() {
    unsigned char receive_data[8];
    
    if (i2c_init() < 0) {
        return 1;
    }
    
    printf("Sending data...\n");
    if (i2c_send(hex_array, sizeof(hex_array))) 
    {
        i2c_close();
        return 1;
    }

    printf("Receiving data...\n");
    if (i2c_receive(receive_data, 6)) {
        i2c_close();
        return 1;
    }
    usleep(10000);

    i2c_close(i2c_fd);
    return 0;
}