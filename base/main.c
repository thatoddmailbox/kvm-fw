#include "stm8/clock.h"
#include "stm8/i2c_slave.h"
#include "stm8/i2cbb.h"
#include "stm8/timer.h"
#include "stm8/uart.h"

#include "base/fsusb74.h"
#include "base/tmds361b.h"

#include "shared/comms.h"

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
	i2c_slave_init();

	uint8_t hdmi_a = 1;
	uint8_t hdmi_b = 1;
	uint8_t usb = 3;

	fsusb74_init();
	fsusb74_select_port(usb - 1);

	uart_write_string("Hello from base\r\n");

	i2cbb_init();

	tmds361b_select_port(hdmi_a);

	while (1) {
		// wait for ADDR bit to go high
		while ((*I2C_SR1 & I2C_SR1_ADDR) == 0) {}

		// we got something!
		// what direction is it?
		bool should_write = ((*I2C_SR3 & I2C_SR3_TRA) != 0);
		uart_write_string(should_write ? "\r\nshould write\r\n" : "\r\nshould read\r\n");
		if (should_write) {
			// data is being requested from us
			i2c_slave_write(hdmi_a << 4 | hdmi_b << 2 | usb);
		} else {
			// we are getting some data
			uint8_t data = i2c_slave_read();

			uint8_t data_command = data & ~0x3;
			uint8_t data_value = data & 0x3;

			num_to_hex(data_value);

			if (data == BASE_COMMAND_GET_STATE) {
				// currently, we have to do nothing
				// we just assume all reads (when we should write) are for the state
				// eventually, at some point, there might be other commands
				uart_write_string("get state");
			} else if (data_command == BASE_COMMAND_SET_HDMI_A) {
				// set hdmi a
				uart_write_string("set hdmi A to ");
				uart_write_string(hex_output);

				hdmi_a = data_value;
				tmds361b_select_port(hdmi_a);
			} else if (data_command == BASE_COMMAND_SET_HDMI_B) {
				// set hdmi b
				uart_write_string("set hdmi B to ");
				uart_write_string(hex_output);
			} else if (data_command == BASE_COMMAND_SET_USB) {
				// set usb
				uart_write_string("set usb to ");
				uart_write_string(hex_output);

				usb = data_value;
				fsusb74_select_port(usb - 1);
			}
			uart_write_string("\r\n");
		}
	}

	/*

	// select port 1
	uint8_t port = 1;
	while (1) {
		tmds361b_select_port(port);
		port = (port == 1 ? 3 : 1);
		for (uint8_t q = 0; q < 10; q++)
		{
			for (uint8_t i = 0; i < 100; i++)
			{
				for (uint8_t j = 0; j < 100; j++)
				{
					timer_delay_us(100);
				}
			}
		}
		uart_write_string("yay\r\n");
	}

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
	uart_write_string("\r\n");*/

	return 0;
}