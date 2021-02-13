#ifndef _STM8_TIMER_H
#define _STM8_TIMER_H

#include <stdint.h>

void timer_init();
void timer_delay_us(uint8_t time);

#endif