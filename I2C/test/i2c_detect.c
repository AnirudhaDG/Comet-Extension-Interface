#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define I2C_DEVICE "/dev/i2c-2"  // I2C bus device
#define DEVICE_ADDR 0x16          // Target device address


int i2c_read_data(int file, uint8_t reg, uint8_t *buf, size_t len) {
    if (write(file, &reg, 1) != 1) {
        perror("Failed to write register address");
        return -1;
    }

    if (read(file, buf, len) != (ssize_t)len) {
        perror("Failed to read data");
        return -1;
    }

    return 0;
}

int request_i2c_data(uint8_t address, uint8_t reg, uint8_t *buf, size_t len) {
    int file;

    // Open the I2C device
    if ((file = open(I2C_DEVICE, O_RDWR)) < 0) {
        perror("Failed to open the I2C device");
        return -1;
    }

    // Set the I2C slave address
    if (ioctl(file, I2C_SLAVE, address) < 0) {
          perror("Failed to set I2C slave address");
        close(file);
        return -1;
    }

    // Read the data
    if (i2c_read_data(file, reg, buf, len) < 0) {
        close(file);
        return -1;
    }

    close(file);
    return 0;
}

int main() {
    uint8_t data[2]; // Buffer for received data
    
    // Example: Read 2 bytes from register 0x00 of device 0x11
    if (request_i2c_data(DEVICE_ADDR, 0x00, data, sizeof(data)) == 0) {
        printf("Received data: 0x%02X 0x%02X\n", data[0], data[1]);
    } else {
        printf("Failed to read data from device\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
