#include "../inc/identification.h"
#include "../inc/detection.h"

int main() {
    int result = gpio_interrupt_detect("gpiochip1", 12, 5);

    if (result == 1) {
        printf("SUCCESS: Interrupt detected!\n");
    } else {
        printf("RESULT: Timeout or error occurred\n");
    }

}