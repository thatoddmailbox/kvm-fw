#include "stm8/clock.h"
#include "stm8/i2c.h"
#include "stm8/uart.h"

#define PCAL6416_ADDRESS 0x40
#define IS31FL3218_ADDRESS 0xA8

int main() {
	clock_init();
	uart_init();
	i2c_init_master();

	uart_write_string("Hello\r\n");

	i2c_start();
	uart_write_string("started\r\n");
	bool response = i2c_write_address(PCAL6416_ADDRESS);
	uart_write_string("wrote\r\n");
	if (response) {
		uart_write_string("found\r\n");
	} else {
		uart_write_string("not found\r\n");
	}
	i2c_stop();

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