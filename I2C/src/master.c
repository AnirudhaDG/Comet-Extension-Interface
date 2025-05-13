#include "../inc/i2c_handler.h"
#include "../../detection/inc/detection.h"

uint8_t hex_array[] = {0xAA, 0x55, 0x01, 0xFF, 0x00, 0x69, 0x88, 0x96};

int main() {
    int result = gpio_interrupt_detect("gpiochip1", 12, 5);

    if (result == 1) {
        printf("Interrupt detected!\n");
    } else {
        printf("Timeout or error occurred\n");
    }
    
    unsigned char receive_data[8];

    int i2c_fd = i2c_init();

    if (i2c_fd < 0) {
        return 1;
    }
    
    printf("Sending data...\n");
    if (i2c_send(hex_array, sizeof(hex_array))) 
    {
        i2c_close();
        return 1;
    }

    printf("Receiving data...\n");
    if (i2c_receive(receive_data, 8)) {
        i2c_close();
        return 1;
    }

    printf("Received: '%s'\n", receive_data);

    i2c_close(i2c_fd);
    return 0;
}