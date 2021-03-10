#ifndef _STM8_I2C_SHARED_H
#define _STM8_I2C_SHARED_H

#include <stdbool.h>
#include <stdint.h>

#include "stm8/registers.h"

inline void i2c_shared_init() {
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

#endif