#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>
#include <stdint.h>
//#include "identification.h"

// Function to configure UART
int configure_uart(int fd, int baudrate) {
    struct termios options;
    
    // Get current port settings
    if (tcgetattr(fd, &options) != 0) {
        perror("tcgetattr failed");
        return -1;
    }

    // Set baud rate
    speed_t speed;
    switch (baudrate) {
        case 9600:   speed = B9600; break;
        case 19200:  speed = B19200; break;
        case 38400:  speed = B38400; break;
        case 57600:  speed = B57600; break;
        case 115200: speed = B115200; break;
        default:
            fprintf(stderr, "Unsupported baud rate\n");
            return -1;
    }
    cfsetispeed(&options, speed);
    cfsetospeed(&options, speed);

    // Configure other settings:
    options.c_cflag &= ~PARENB;   // No parity
    options.c_cflag &= ~CSTOPB;   // 1 stop bit
    options.c_cflag &= ~CSIZE;    // Clear data size bits
    options.c_cflag |= CS8;       // 8 data bits
    options.c_cflag &= ~CRTSCTS;  // No hardware flow control
    options.c_cflag |= CREAD | CLOCAL; // Enable receiver, ignore modem lines

    // Raw input/output
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_oflag &= ~OPOST;

    // Set the new options
    if (tcsetattr(fd, TCSANOW, &options) != 0) {
        perror("tcsetattr failed");
        return -1;
    }

    return 0;
}

// Function to write data to UART
int uart_write(int fd, const char *data, size_t length) {
    ssize_t bytes_written = write(fd, data, length);
    if (bytes_written < 0) {
        perror("uart_write failed");
        return -1;
    }
    return bytes_written;
}

// Function to read data from UART
int uart_read(int fd, char *buffer, size_t buffer_size) {
    ssize_t bytes_read = read(fd, buffer, buffer_size - 1); // Leave space for null terminator
    if (bytes_read < 0) {
        perror("uart_read failed");
        return -1;
    }
    buffer[bytes_read] = '\0'; // Null-terminate the string
    return bytes_read;
}


int connect_uart(const char *portname, int baudrate) {
    // const char *portname = "/dev/ttymxc2";
    // int baudrate = 115200;
    
    // Open UART device
    int uart_fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (uart_fd < 0) {
        perror("Error opening UART device");
        return -1;
    }

    // Configure UART
    if (configure_uart(uart_fd, baudrate) < 0) {
        close(uart_fd);
        return -1;
    }
    else
    {
        printf("UART device opened and configured successfully\n");
    }

    uint8_t hex_array[] = {0xAA, 0x55, 0x01, 0xFF, 0x00, 0x69, 0x88, 0x96};
    int array_size = sizeof(hex_array) / sizeof(hex_array[0]);

    printf("Writing hex array!\n");

    if (uart_write(uart_fd, (char*)hex_array, array_size) < 0) {
        perror("UART write failed");
        close(uart_fd);
        return -1;
    }
    else {
        printf("Done writing %d bytes!\n", array_size);
    }


    // Write String:

    // char write_data[] = "aa";
    // char read_buffer[8];

    // printf("Writing!\n");

    // if (uart_write(uart_fd, write_data, strlen(write_data)) < 0) 
    // {
    //     close(uart_fd);
    //     return EXIT_FAILURE;
    // }
    // else
    // {
    //     printf("Done Writing!\n");
    // }

    
    // Read Data

    char read_buffer[10];

    // Set timeout
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(uart_fd, &readfds);
    
    int ret = select(uart_fd + 1, &readfds, NULL, NULL, &timeout);
    if (ret < 0) {
        perror("select failed");
    } else if (ret == 0) {
        printf("Timeout reached, no data received\n");
    } else {
        // Data available to read
        int bytes_read = uart_read(uart_fd, read_buffer, sizeof(read_buffer));
        if (bytes_read > 0) {
            printf("Received %d bytes: %s\n", bytes_read, read_buffer);
        }
    }

    close(uart_fd);
    return 0;
}

// int main(){return 0;}
