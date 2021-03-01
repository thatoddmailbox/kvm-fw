#include "base/tmds361b.h"

void tmds361b_write_register(uint8_t address, uint8_t data) {
	i2cbb_start();
	i2cbb_write(TMDS361B_ADDRESS);
	i2cbb_write(address);
	i2cbb_write(data);
	i2cbb_stop();
}