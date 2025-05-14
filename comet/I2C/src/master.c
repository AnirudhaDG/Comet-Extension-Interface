#include "../inc/i2c_handler.h"
#include "../../detection/inc/detection.h"

uint8_t hex_array[] = {0xAA, 0x55, 0x01, 0xFF, 0x00, 0x69, 0x88, 0xFF};

const uint8_t key_size = 8;

int main() {
    // int result = gpio_interrupt_detect("gpiochip1", 12, 5);

    // if (result == 1) {
    //     printf("Interrupt detected!\n");
    // } else {
    //     printf("Timeout or error occurred\n");
    //     return -1;
    // }

    uint8_t receive_data[key_size];
    
    if (connect_i2c(hex_array, receive_data, key_size) > 0)
    {
        for (size_t i = 0; i < key_size; i++) {
            printf("0x%02x", receive_data[i]);
            if (i < key_size - 1) {
                printf(", ");
            }
        }
        printf("\n");
    }
    
    return 0;
}