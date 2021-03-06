#include "base/tmds361b.h"
#include "stm8/i2cbb.h"

static const uint8_t port_flags[4] = {
	TMDS361B_REGISTER_1_STANDBY,
	TMDS361B_REGISTER_1_PORT1,
	TMDS361B_REGISTER_1_PORT2,
	TMDS361B_REGISTER_1_PORT3
};

void tmds361b_select_port(uint8_t port) {
	i2cbb_start();
	i2cbb_write(TMDS361B_ADDRESS);
	i2cbb_write(TMDS361B_REGISTER_1);
	i2cbb_write(port_flags[port] | TMDS361B_REGISTER_1_OVS3);
	i2cbb_stop();
}

void tmds361b_write_register(uint8_t address, uint8_t data) {
	i2cbb_start();
	i2cbb_write(TMDS361B_ADDRESS);
	i2cbb_write(address);
	i2cbb_write(data);
	i2cbb_stop();
}