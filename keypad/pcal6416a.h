#ifndef _KEYPAD_PCAL6416A_H
#define _KEYPAD_PCAL6416A_H

#include <stdint.h>

void pcal6416a_init();
uint16_t pcal6416a_read_pins();

#endif