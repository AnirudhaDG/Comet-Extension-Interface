#include "../inc/UART_handler.h"
#include "../../detection/inc/detection.h"

int main() {
    int result = gpio_interrupt_detect("gpiochip1", 12, 5);

    if (result == 1) {
        printf("Interrupt detected!\n");
    } else {
        printf("Timeout or error occurred\n");
    }

    const char *portname = "/dev/ttymxc2";
    int baudrate = 115200;

    connect_uart(portname, baudrate);

}