#ifndef _BASE_FSUSB_H
#define _BASE_FSUSB_H

#include <stdint.h>

void fsusb74_init();
void fsusb74_select_port(uint8_t index);

#endif