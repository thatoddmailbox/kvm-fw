#ifndef _STM8_I2C_H
#define _STM8_I2C_H

#include <stdbool.h>
#include <stdint.h>

#define I2C_WRITE 0x0
#define I2C_READ 0x1

void i2c_init_master();
void i2c_start();
void i2c_stop();
uint8_t i2c_read(bool should_ack);
void i2c_write(uint8_t data);
bool i2c_write_address(uint8_t addr);

#endif