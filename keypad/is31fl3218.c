#include "keypad/is31fl3218.h"
#include "stm8/i2c_master.h"

bool is31fl3218_init() {
	// reset its state
	bool response = i2c_write_reg(IS31FL3218_ADDRESS, IS31FL3218_REG_RESET, 0);
	if (!response) {
		return response;
	}

	// disable shutdown mode
	return i2c_write_reg(IS31FL3218_ADDRESS, IS31FL3218_REG_SHUTDOWN, 1);
}

void is31fl3218_set_brightness(uint8_t b) {
	i2c_start();

	bool response = i2c_write_address(IS31FL3218_ADDRESS | I2C_WRITE);
	if (!response) {
		i2c_stop();
		return;
	}
	i2c_write(IS31FL3218_REG_PWM_01);
	for (uint8_t i = 0; i < IS31FL3218_CHANNEL_COUNT; i++) {
		i2c_write(b);
	}

	i2c_stop();
}

void is31fl3218_set_leds(uint16_t leds) {
	uint8_t ctrl1 = (uint8_t) (leds & 0x3F);
	i2c_write_reg(IS31FL3218_ADDRESS, IS31FL3218_REG_LED_1, ctrl1);

	uint8_t ctrl2 = (uint8_t) ((leds & 0xFC0) >> 6);
	i2c_write_reg(IS31FL3218_ADDRESS, IS31FL3218_REG_LED_2, ctrl2);
}

void is31fl3218_update() {
	i2c_write_reg(IS31FL3218_ADDRESS, IS31FL3218_REG_UPDATE, 0);
}