/*
Repository: 
Thing to keep in mind:
- Pull up only to 3v3. 5v has exaggerated debounce
- 1v8 is nominal 
*/

#include <gpiod.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include "detection.h"

int gpio_interrupt_detect(const char *chipname, unsigned int line_num, int timeout_sec) {
    struct gpiod_chip *chip;
    struct gpiod_line *line;
    struct timespec timeout;
    int ret;

    // Open GPIO chip
    chip = gpiod_chip_open_by_name(chipname);
    if (!chip) {
        perror("Error opening GPIO chip");
        return -1;
    }

    // Get GPIO line
    line = gpiod_chip_get_line(chip, line_num);
    if (!line) {
        perror("Error getting GPIO line");
        gpiod_chip_close(chip);
        return -1;
    }

    // Request interrupt detection on rising edge
    ret = gpiod_line_request_rising_edge_events(line, "interrupt-detection");
    if (ret < 0) {
        perror("Error requesting events");
        gpiod_line_release(line);
        gpiod_chip_close(chip);
        return -1;
    }

    // Set up timeout
    struct timespec *timeout_ptr = NULL;
    if (timeout_sec > 0) {
        timeout.tv_sec = timeout_sec;
        timeout.tv_nsec = 0;
        timeout_ptr = &timeout;
    }

    // Wait for event
    ret = gpiod_line_event_wait(line, timeout_ptr);
    
    // Clean up resources
    gpiod_line_release(line);
    gpiod_chip_close(chip);


    if (ret == 1) 
    {
        return 1;  
    } 

    else if (ret == 0) 
    {
        return -1;
    } 

    return 0;

}

// int main() {
//     int result = gpio_interrupt_detect("gpiochip1", 12, 5);
//     if (result == 1) {
//         printf("SUCCESS: Interrupt detected!\n");
//     } else {
//         printf("RESULT: Timeout or error occurred\n");
//     }
//     return 0;
// }