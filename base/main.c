#include "stm8/clock.h"
#include "stm8/timer.h"
#include "stm8/uart.h"

int main() {
	clock_init();
	timer_init();
	uart_init();

	uart_write_string("Hello from base\r\n");

	while (1) {
		uart_write_string("yay\r\n");
		for (uint8_t i = 0; i < 100; i++)
		{
			for (uint8_t j = 0; j < 100; j++)
			{
				timer_delay_us(100);
			}
		}
	}

	return 0;
}