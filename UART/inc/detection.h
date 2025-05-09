#ifndef DETECTION_H
#define DETECTION_H

#include <gpiod.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

int gpio_interrupt_detect(const char *chipname, unsigned int line_num, int timeout_sec);

#endif