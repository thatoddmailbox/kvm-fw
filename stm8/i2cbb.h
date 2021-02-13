#ifndef _STM8_I2CBB_H
#define _STM8_I2CBB_H

#include <stdbool.h>
#include <stdint.h>

void i2cbb_init();
void i2cbb_start();
void i2cbb_stop();
uint8_t i2cbb_read();
bool i2cbb_write(uint8_t data);

#endif