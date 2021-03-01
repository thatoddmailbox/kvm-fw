#ifndef _BASE_TMDS361B_H
#define _BASE_TMDS361B_H

#include <stdint.h>

#define TMDS361B_ADDRESS 0x58

#define TMDS361B_REGISTER_1 0x1
#define TMDS361B_REGISTER_2 0x2
#define TMDS361B_REGISTER_3 0x3

void tmds361b_write_register(uint8_t address, uint8_t data);

#endif