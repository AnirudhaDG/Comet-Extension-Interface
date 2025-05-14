#include "../inc/UART_handler.h"
#include "../../detection/inc/detection.h"

uint8_t hex_array[] = {0xAA, 0x55, 0x01, 0xFF, 0x00, 0x69, 0x88, 0xFF};

int main() {
    int result = gpio_interrupt_detect("gpiochip1", 12, 5);

    if (result == 1) {
        printf("Interrupt detected!\n");
    } else {
        printf("Timeout or error occurred\n");
    }

    const char *portname = "/dev/ttymxc2";
    int baudrate = 115200;

    connect_uart(portname, baudrate, hex_array);

}