#include "../inc/UART_handler.h"
#include "../../detection/inc/detection.h"

uint8_t hex_array[] = {0xAA, 0x55, 0x01, 0xFF, 0x00, 0x69, 0x88, 0xFF};
uint8_t received_data[];

int main() {
    // int result = gpio_interrupt_detect("gpiochip1", 12, 5);

    // if (result == 1) {
    //     printf("Interrupt detected!\n");
    // } else {
    //     printf("Timeout or error occurred\n");
    // }

    const char *portname = "/dev/ttymxc2";
    int baudrate = 115200;

    // if (connect_uart(portname, baudrate, hex_array, key_size, receive_data))
    // {
    //     printf("\nVALID PACKET: ");
    //     for (int k = 0; k < 8; k++) {
    //         printf("0x%02X ", received_data[k]);
    //     }
    //     printf("\n");
    // }

}