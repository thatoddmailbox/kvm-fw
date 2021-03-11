#include "stm8/i2c_slave.h"
#include "stm8/i2c_shared.h"
#include "stm8/registers.h"

#include "shared/comms.h"

void i2c_slave_init() {
	// turn off i2c peripheral
	*I2C_CR1 = 0;

	// need to set ADDCONF to 1
	// leave everything else as 0 to use 7-bit addresses
	*I2C_OARH = I2C_OARH_ADDCONF;
	*I2C_OARL = BASE_I2C_ADDRESS;

	i2c_shared_init();

	// enable acknowledges
	*I2C_CR2 = I2C_CR2_ACK;
}

uint8_t i2c_slave_read() {
	while ((*I2C_SR1 & I2C_SR1_RXNE) == 0) {}
	return *I2C_DR;
}