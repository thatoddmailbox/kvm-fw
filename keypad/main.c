#include "stm8/clock.h"
#include "stm8/i2c.h"
#include "stm8/uart.h"

#include "keypad/is31fl3218.h"

#define PCAL6416_ADDRESS 0x40

int main() {
	clock_init();
	uart_init();
	i2c_init_master();

	uart_write_string("Hello\r\n");

	is31fl3218_init();
	is31fl3218_set_brightness(0x80);
	is31fl3218_set_leds(1);
	is31fl3218_update();

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