/*
Thing to keep in mind:
- Pull up only to 3v3. 5v has exaggerated debounce
- 1v8 is nominal 
*/


#include <gpiod.h>
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <stdbool.h>


#define DEBOUNCE_TIME_MS 70  // Adjust as needed

static volatile bool running = true;

void signal_handler(int sig) {
    running = false;
}

int ISR_detection()
{
    
}

int main() {
    int test_counter = 0;
    const char *chipname = "gpiochip1";
    const unsigned int line_num = 12;
    struct timespec last_event = {0};
    bool connected_printed = false;

    struct gpiod_chip *chip = gpiod_chip_open_by_name(chipname);
    struct gpiod_line *line = gpiod_chip_get_line(chip, line_num);
    gpiod_line_request_rising_edge_events(line, "Extention-Detection");
    signal(SIGINT, signal_handler);


    while (running) {
        if (gpiod_line_event_wait(line, NULL) == 1) {
            struct gpiod_line_event event;
            gpiod_line_event_read(line, &event);

            // Added for debounce, recommend using RC filter
            long elapsed_ms = (event.ts.tv_sec - last_event.tv_sec) * 1000 + 
                             (event.ts.tv_nsec - last_event.tv_nsec) / 1000000;

            if (elapsed_ms >= DEBOUNCE_TIME_MS) {
                // printf("connected\n");  // Print ONCE per valid trigger
                test_counter++;
                printf("Counter: %d", test_counter);
                printf("\n");
                fflush(stdout);
                last_event = event.ts; 
            }
        }
    }

    gpiod_line_release(line);
    gpiod_chip_close(chip);
    return 0;
}
