#include "keypad/pcal6416a.h"
#include "stm8/i2c.h"

#define PCAL6416A_ADDRESS 0x40

#define PCAL6416A_INPUT_0 0x00
#define PCAL6416A_INPUT_1 0x01
#define PCAL6416A_OUTPUT_0 0x02
#define PCAL6416A_OUTPUT_1 0x03
#define PCAL6416A_INVERT_0 0x04
#define PCAL6416A_INVERT_1 0x05
#define PCAL6416A_CONFIG_0 0x06
#define PCAL6416A_CONFIG_1 0x07
#define PCAL6416A_OUTPUT_0_LOW 0x40
#define PCAL6416A_OUTPUT_0_HIGH 0x41
#define PCAL6416A_OUTPUT_1_LOW 0x42
#define PCAL6416A_OUTPUT_1_HIGH 0x43
#define PCAL6416A_INPUT_LATCH_0 0x44
#define PCAL6416A_INPUT_LATCH_1 0x45
#define PCAL6416A_PULL_ENABLE_0 0x46
#define PCAL6416A_PULL_ENABLE_1 0x47
#define PCAL6416A_PULL_SELECT_0 0x48
#define PCAL6416A_PULL_SELECT_1 0x49
#define PCAL6416A_INTERRUPT_MASK_0 0x4A
#define PCAL6416A_INTERRUPT_MASK_1 0x4B
#define PCAL6416A_INTERRUPT_STATUS_0 0x4C
#define PCAL6416A_INTERRUPT_STATUS_1 0x4D
#define PCAL6416A_OUTPUT_PORT_CONFIG 0x4F

void pcal6416a_init() {
	// set all pins to inputs
	// should be the case by default, but just in case
	i2c_write_reg(PCAL6416A_ADDRESS, PCAL6416A_CONFIG_0, 0xFF);
	i2c_write_reg(PCAL6416A_ADDRESS, PCAL6416A_CONFIG_1, 0xFF);

	// set all pins to have pull-downs
	i2c_write_reg(PCAL6416A_ADDRESS, PCAL6416A_PULL_SELECT_0, 0);
	i2c_write_reg(PCAL6416A_ADDRESS, PCAL6416A_PULL_SELECT_1, 0);

	// enable all pull resistors
	i2c_write_reg(PCAL6416A_ADDRESS, PCAL6416A_PULL_ENABLE_0, 0xFF);
	i2c_write_reg(PCAL6416A_ADDRESS, PCAL6416A_PULL_ENABLE_1, 0xFF);
}

uint8_t pcal6416a_read_reg(uint8_t reg) {
	i2c_start();

	bool response = i2c_write_address(PCAL6416A_ADDRESS | I2C_WRITE);
	if (!response) {
		i2c_stop();
		return 0;
	}
	i2c_write(reg);

	i2c_stop();

	i2c_start();
	i2c_write_address(PCAL6416A_ADDRESS | I2C_READ);
	uint8_t value = i2c_read(false);
	i2c_stop();
	return value;
}

uint16_t pcal6416a_read_pins() {
	uint8_t lower = pcal6416a_read_reg(PCAL6416A_INPUT_0);
	uint8_t upper = pcal6416a_read_reg(PCAL6416A_INPUT_1);
	return ((uint16_t) upper << 8) | (uint16_t) lower;
}