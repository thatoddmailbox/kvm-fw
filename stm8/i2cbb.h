#ifndef _STM8_I2CBB_H
#define _STM8_I2CBB_H

#include <stdbool.h>

void i2cbb_init();
void i2cbb_start();
uint8_t i2cbb_read();
void i2cbb_write(uint8_t data);

#endif