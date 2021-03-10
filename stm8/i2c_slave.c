#include "stm8/i2c_slave.h"
#include "stm8/i2c_shared.h"
#include "stm8/registers.h"

#include "shared/comms.h"

void i2c_init_slave() {
	// need to set ADDCONF to 1
	// leave everything else as 0 to use 7-bit addresses
	*I2C_OARH = I2C_OARH_ADDCONF;
	*I2C_OARL = BASE_I2C_ADDRESS;

	i2c_shared_init();
}