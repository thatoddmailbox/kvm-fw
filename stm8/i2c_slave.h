#ifndef _STM8_I2C_SLAVE_H
#define _STM8_I2C_SLAVE_H

#include <stdint.h>

void i2c_slave_init();
uint8_t i2c_slave_read();
void i2c_slave_write(uint8_t data);

#endif