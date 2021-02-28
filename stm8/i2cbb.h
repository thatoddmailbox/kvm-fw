#ifndef _STM8_I2CBB_H
#define _STM8_I2CBB_H

#include <stdbool.h>
#include <stdint.h>

#define I2CBB_READ 0
#define I2CBB_WRITE 1

void i2cbb_init();
void i2cbb_start();
void i2cbb_stop();
uint8_t i2cbb_read();
bool i2cbb_write(uint8_t data);

#endif