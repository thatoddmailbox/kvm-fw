#include "stm8/clock.h"
#include "stm8/i2cbb.h"
#include "stm8/timer.h"
#include "stm8/uart.h"

#include "base/fsusb74.h"
#include "base/tmds361b.h"

char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
char hex_output[3];

void num_to_hex(uint8_t num) {
	hex_output[0] = hex[(num & 0xF0) >> 4];
	hex_output[1] = hex[(num & 0xF)];
	hex_output[2] = '\0';
}

int main() {
	clock_init();
	timer_init();
	uart_init();

	fsusb74_init();
	// fsusb74_select_port(2);

	uart_write_string("Hello from base\r\n");

	i2cbb_init();

	// select port 2
	i2cbb_start();
	i2cbb_write(TMDS361B_ADDRESS);
	i2cbb_write(TMDS361B_REGISTER_1);
	i2cbb_write((1 << 7) | 0x10);
	i2cbb_stop();

	// read status register
	i2cbb_start();
	i2cbb_write(TMDS361B_ADDRESS);
	i2cbb_write(TMDS361B_REGISTER_2);
	i2cbb_stop();
	i2cbb_start();
	i2cbb_write(TMDS361B_ADDRESS | I2CBB_WRITE);
	uint8_t value = i2cbb_read();
	i2cbb_stop();
	num_to_hex(value);
	uart_write_string(hex_output);
	uart_write_string("\r\n");

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