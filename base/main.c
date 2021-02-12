#include "stm8/clock.h"
#include "stm8/uart.h"

int main() {
	clock_init();
	uart_init();

	uart_write_string("Hello from base\r\n");

	while (1) {}

	return 0;
}