#include "stm8/clock.h"
#include "stm8/i2c_master.h"
#include "stm8/timer.h"
#include "stm8/uart.h"

#include "keypad/is31fl3218.h"
#include "keypad/pcal6416a.h"

#include "shared/comms.h"

int main() {
	clock_init();
	timer_init();
	uart_init();
	i2c_master_init();

	uart_write_string("Hello\r\n");

	is31fl3218_init();
	pcal6416a_init();

	is31fl3218_set_brightness(0x1);

	i2c_start();
	bool ack = i2c_write_address(BASE_I2C_ADDRESS);
	uart_write_string(ack ? "ack\r\n" : "nak\r\n");
	i2c_write(0x5E);
	i2c_stop();

	char c = '1';
	uint16_t led_state = 0;
	uint16_t previous_pins = 0;
	while (1) {
		uint16_t pins = pcal6416a_read_pins();

		// we want to find who changed and also used to be high
		uint16_t changes = (pins ^ previous_pins) & previous_pins;
		previous_pins = pins;

		if (changes != 0) {
			led_state ^= changes;
			is31fl3218_set_leds(led_state & 0x1FF);
			is31fl3218_update();

			uart_write_byte(c);
			uart_write_string("\r\n");
			c++;
			if (c >= '9') {
				c = '1';
			}
		}
	}

	uint8_t b = 0;
	bool dir = true;
	while (1) {
		if (dir) {
			b++;
			if (b == 0) {
				dir = false;
			}
		} else {
			b--;
			if (b == 0) {
				dir = true;
			}
		}
		is31fl3218_set_brightness(b);
		is31fl3218_update();

		for (unsigned short i = 0; i < 100; i++) {
			__asm__("nop");
		}
	}

	return 0;
}