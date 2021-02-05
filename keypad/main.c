#include "stm8/clock.h"
#include "stm8/uart.h"

int main() {
	clock_init();
	uart_init();

	while (1) {
		uart_write_string("Hello\r\n");
	}

	return 0;
}