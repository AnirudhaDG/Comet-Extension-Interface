/*
To Do: 
- CRC generator
*/

#include "./I2C/inc/i2c_handler.h"
#include "./UART/inc/UART_handler.h"
#include "./detection/inc/detection.h"

const char *portname = "/dev/ttymxc2";
int baudrate = 115200;

uint8_t hex_array[] = {0xAA, 0x55, 0x01, 0xFF, 0x00, 0x69, 0x88, 0xFF};
const uint8_t key_size = 8;

int main()
{
    printf("\nWaiting for Extension\n");
    if (gpio_interrupt_detect("gpiochip1", 12, 5) == 1)
    {
        printf("Extension detected!\n");
    } else {
        printf("Timeout or error occurred");
        return -1;
    }
    printf("\n");

    uint8_t receive_data[key_size];

    int i2c_ret = connect_i2c(hex_array, receive_data, key_size);

    if (i2c_ret == 1)
    {
        printf("\nConnected to extension over I2C with ID: ");
        for (size_t i = 2; i < key_size - 2; i++) {
            printf("0x%02x", receive_data[i]);
            if (i < key_size - 1) {
                printf(" ");
            }
        }
        printf("\n\n");
        return 1;
    }

    while(1)
    {
        printf("\n\nAttempting Connection over UART");
        if (connect_uart(portname, baudrate, hex_array, key_size, receive_data))
        {
            printf("\n\nConnected to Extension over UART with ID: ");
            for (int k = 2; k < key_size - 2; k++) {
                printf("0x%02X ", receive_data[k]);
            }
            printf("\n");
            return 0;
        }
        usleep(3000000);
    }
}