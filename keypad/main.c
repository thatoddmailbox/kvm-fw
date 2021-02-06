#include "stm8/clock.h"
#include "stm8/i2c.h"
#include "stm8/uart.h"

#include "keypad/is31fl3218.h"
#include "keypad/pcal6416a.h"

int main() {
	clock_init();
	uart_init();
	i2c_init_master();

	uart_write_string("Hello\r\n");

	is31fl3218_init();
	pcal6416a_init();

	is31fl3218_set_brightness(0x80);

	uint16_t led_state = 1;
	while (1) {
		is31fl3218_set_leds(led_state);
		is31fl3218_update();

		led_state = led_state << 1;
		if (led_state == (1 << 9)) {
			led_state = 1;
		}

		for (unsigned short y = 0; y < 20; y++) {
			for (unsigned short z = 0; z < 16000; z++) {
				__asm__("nop");
			}
		}
	}

	char c = '1';
	while (1) {
		uint16_t pins = pcal6416a_read_pins();
		if (pins != 0) {
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

	while (1) {
		uart_write_string("yay\r\n");
		for (unsigned short q = 0; q < 100; q++) {
			for (unsigned short i = 0; i < 16000; i++) {
				__asm__("nop");
			}
		}
	}

	return 0;
}