#include "stm8/clock.h"
#include "stm8/uart.h"

int main() {
	clock_init();
	uart_init();

	while (1) {
		uart_write_byte('A');
		uart_write_byte('B');
		uart_write_byte('C');
		uart_write_byte('\r');
		uart_write_byte('\n');
	}

	return 0;
}