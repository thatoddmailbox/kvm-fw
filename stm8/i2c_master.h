#ifndef _STM8_I2C_MASTER_H
#define _STM8_I2C_MASTER_H

#include <stdbool.h>
#include <stdint.h>

#define I2C_WRITE 0x0
#define I2C_READ 0x1

void i2c_master_init();
void i2c_start();
void i2c_stop();
uint8_t i2c_master_read(bool should_ack);
void i2c_write(uint8_t data);
bool i2c_write_address(uint8_t addr);
bool i2c_write_reg(uint8_t addr, uint8_t reg, uint8_t data);

#endif