#include "stm8/i2c.h"
#include "stm8/registers.h"

void i2c_init_master() {
	// i2c scl is PB4; i2c sda is PB5
	*PB_DDR |= (1 << 5) | (1 << 4); // set as outputs
	*PB_CR1 &= ~((1 << 5) | (1 << 4)); // set as floating
	*PB_ODR |= (1 << 5) | (1 << 4); // set them high
	*PB_CR2 |= (1 << 5) | (1 << 4); // set them to be speedy bois

	// see section 21.4.2 of RM0016 for init procedure

	// turn off i2c peripheral
	*I2C_CR1 = 0;

	// we are using 16 MHz fMASTER, and that's what gets passed to the I2C peripheral
	*I2C_FREQR = 16;

	// we want 100 kHZ (standard speed)
	// that means I2C_CCR = 0x50
	*I2C_CCRH = 0; // seventh bit sets standard mode
	*I2C_CCRL = 0x50;

	// standard mode has max rise time of 1000 ns
	// fMASTER = 16 MHz; tMASTER = 62.5 ns
	// 1000 ns / 62.5 ns = 16 + 1 = 17
	*I2C_TRISER = 17;

	// turn on i2c peripheral
	*I2C_CR1 = I2C_CR1_PE;
}

void i2c_start() {
	*I2C_CR2 |= I2C_CR2_START;
	while ((*I2C_SR1 & I2C_SR1_SB) == 0) {}
}

void i2c_stop() {
	*I2C_CR2 |= I2C_CR2_STOP;
	while ((*I2C_SR3 & I2C_SR3_MSL) == 0) {}
}

uint8_t i2c_read(bool should_ack) {
	if (should_ack) {
		*I2C_CR2 |= I2C_CR2_ACK;
	} else {
		*I2C_CR2 &= ~I2C_CR2_ACK;
	}
	while ((*I2C_SR1 & I2C_SR1_RXNE) == 0) {}
	return *I2C_DR;
}

void i2c_write(uint8_t data) {
	*I2C_DR = data;
	while ((*I2C_SR1 & I2C_SR1_TXE) == 0) {}
}

bool i2c_write_address(uint8_t addr) {
	*I2C_DR = addr;
	while (1) {
		// check for acknowledge failure
		if (*I2C_SR2 & I2C_SR2_AF) {
			// clear AF bit
			*I2C_SR2 &= ~I2C_SR2_AF;

			return false;
		}

		if ((*I2C_SR1 & I2C_SR1_ADDR) != 0) {
			// we got an ACK of the address!
			break;
		}
	}

	// read SR3 to clear SR1's ADDR bit
	(void) *I2C_SR3;

	*I2C_CR2 |= I2C_CR2_ACK;

	return true;
}

bool i2c_write_reg(uint8_t addr, uint8_t reg, uint8_t data) {
	i2c_start();

	bool response = i2c_write_address(addr | I2C_WRITE);
	if (!response) {
		i2c_stop();
		return false;
	}
	i2c_write(reg);
	i2c_write(data);

	i2c_stop();

	return true;
}