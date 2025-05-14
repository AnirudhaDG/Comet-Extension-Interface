/*
TO DO:
- find a way to change the value of the packet from 255 to a cont byte stream
- find if one function call structure if better than this structure
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>
#include "../inc/UART_handler.h"

#define START_BYTE 0xAA
#define END_BYTE 0xFF

int configure_uart(int fd, int baudrate) {
    struct termios options;

    if (tcgetattr(fd, &options) != 0) {
        perror("tcgetattr failed");
        return -1;
    }

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

    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_oflag &= ~OPOST;

    // Set the new options
    if (tcsetattr(fd, TCSANOW, &options) != 0) {
        perror("tcsetattr failed");
        return -1;
    }

    return 0;
}

int uart_write(int fd, const char *data, size_t length) {
    ssize_t bytes_written = write(fd, data, length);
    if (bytes_written < 0) {
        perror("uart_write failed");
        return -1;
    }
    return bytes_written;
}

int uart_read(int fd, char *buffer, size_t buffer_size) {
    ssize_t bytes_read = read(fd, buffer, buffer_size);
    if (bytes_read < 0) {
        perror("uart_read failed");
        return -1;
    }
    return bytes_read;
}

int process_uart_data(const uint8_t *data, int length, const uint8_t key_size, uint8_t *output) {
    uint8_t valid_packet[key_size];
    bool packet_found = false;
    for (int i = 0; i < length; i++) {
        if (data[i] == START_BYTE && (i + key_size - 1) < length) {
            for (int j = 0; j < key_size; j++) {
                valid_packet[j] = data[i + j];
            }

            if (valid_packet[key_size - 1] == END_BYTE) 
            {
                packet_found = true;
                memcpy(output, valid_packet, key_size);
                // printf("VALID PACKET: ");
                // for (int k = 0; k < key_size; k++) {
                //     printf("0x%02X ", valid_packet[k]);
                // }
                // printf("\n");
                return 1;
            } 
            
            else {
                // printf("DISCARDED (Last byte not 0xFF): ");
                // for (int k = 0; k < key_size; k++) {
                //     printf("0x%02X ", valid_packet[k]);
                // }
                // printf("\n");
                return 0;
            }
        }
    }
}

int check_timeout(int uart_fd, int time)
{
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(uart_fd, &readfds);

    int ret = select(uart_fd + 1, &readfds, NULL, NULL, &timeout);

    if (ret < 0) {
        perror("select failed");
        return -1;
    } else if (ret == 0) {
        printf("Timeout reached, no data received\n");
        return -1;
    } 
    else {
        return 1;
    }
}

int connect_uart(const char *portname, int baudrate, uint8_t hex_array[],const uint8_t key_size, uint8_t *output) 
{
    int uart_fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (uart_fd < 0) {
        perror("Error opening UART device");
        return -1;
    }

    if (configure_uart(uart_fd, baudrate) < 0) {
        close(uart_fd);
        return -1;
    }
    else
    {
        printf("UART device opened and configured successfully\n");
    }

    printf("Writing hex array\n");

    if (uart_write(uart_fd, (char*)hex_array, key_size) < 0) {
        perror("UART write failed");
        close(uart_fd);
        return -1;
    }
    else {
        printf("Done writing %d bytes\n", key_size);
    }

    char read_buffer[255]; //have to find a solution for this

    if (check_timeout(uart_fd, 5) > 0)
    {
        int num_bytes = uart_read(uart_fd, read_buffer, 255);
        if (num_bytes) {printf("Data Received!\n");}
        if (process_uart_data(read_buffer, num_bytes, key_size, output))
        {
            printf("Data Validated");
            return 1;
        }
        else {printf("Invalid Data");}
    }

    close(uart_fd);
    return 0;
}
