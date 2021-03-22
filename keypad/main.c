#include "stm8/clock.h"
#include "stm8/i2c_master.h"
#include "stm8/timer.h"
#include "stm8/uart.h"

#include "keypad/is31fl3218.h"
#include "keypad/pcal6416a.h"

#include "shared/comms.h"

void update_leds(uint8_t base_hdmi_a, uint8_t base_hdmi_b, uint8_t base_usb) {
	//			 hdmi A | hdmi B | usb
	//	port 1 | 0		  1		   2
	//	port 2 | 3		  4		   5
	//	port 3 | 6		  7		   8
	uint16_t led_state = (
		(1 << (base_hdmi_a + base_hdmi_a + base_hdmi_a - 3)) |
		(1 << (base_hdmi_b + base_hdmi_b + base_hdmi_b - 3 + 1)) |
		(1 << (base_usb + base_usb + base_usb - 3 + 2))
	);

	is31fl3218_set_leds(led_state & 0x1FF);
	is31fl3218_update();
}

int main() {
	clock_init();
	timer_init();
	uart_init();
	i2c_master_init();

	uart_write_string("Hello\r\n");

	is31fl3218_init();
	pcal6416a_init();

	is31fl3218_set_brightness(0x1);

	// read the current state
	i2c_start();
	i2c_write_address(BASE_I2C_ADDRESS | I2C_WRITE);
	i2c_write(BASE_COMMAND_GET_STATE);
	i2c_stop();
	i2c_start();
	i2c_write_address(BASE_I2C_ADDRESS | I2C_READ);
	uint8_t base_status = i2c_master_read(false);
	i2c_stop();

	uint8_t base_hdmi_a = (base_status >> 4) & 0x3;
	uint8_t base_hdmi_b = (base_status >> 2) & 0x3;
	uint8_t base_usb = base_status & 0x3;

	update_leds(base_hdmi_a, base_hdmi_b, base_usb);

	uint16_t led_state = 0;
	uint16_t previous_pins = 0;
	while (1) {
		uint16_t pins = pcal6416a_read_pins();

		// we want to find who changed and also used to be high
		uint16_t changes = (pins ^ previous_pins) & previous_pins;
		previous_pins = pins;

		if (changes != 0) {
			//			 hdmi A | hdmi B | usb
			//	port 1 | 0		  1		   2
			//	port 2 | 3		  4		   5
			//	port 3 | 6		  7		   8

			uint8_t hdmi_a = 0;
			uint8_t hdmi_b = 0;
			uint8_t usb = 0;

			if ((changes & (1 << 0)) != 0) {
				// hdmi A, port 1
				hdmi_a = 1;
			} else if ((changes & (1 << 3)) != 0) {
				// hdmi A, port 2
				hdmi_a = 2;
			} else if ((changes & (1 << 6)) != 0) {
				// hdmi A, port 3
				hdmi_a = 3;
			}

			if ((changes & (1 << 1)) != 0) {
				// hdmi B, port 1
				hdmi_b = 1;
			} else if ((changes & (1 << 4)) != 0) {
				// hdmi B, port 2
				hdmi_b = 2;
			} else if ((changes & (1 << 7)) != 0) {
				// hdmi B, port 3
				hdmi_b = 3;
			}

			if ((changes & (1 << 2)) != 0) {
				// usb, port 1
				usb = 1;
			} else if ((changes & (1 << 5)) != 0) {
				// usb, port 2
				usb = 2;
			} else if ((changes & (1 << 8)) != 0) {
				// usb, port 3
				usb = 3;
			}

			if (hdmi_a) {
				i2c_start();
				i2c_write_address(BASE_I2C_ADDRESS | I2C_WRITE);
				i2c_write(BASE_COMMAND_SET_HDMI_A | hdmi_a);
				i2c_stop();
				base_hdmi_a = hdmi_a;
			}

			if (hdmi_b) {
				i2c_start();
				i2c_write_address(BASE_I2C_ADDRESS);
				i2c_write(BASE_COMMAND_SET_HDMI_B | hdmi_b);
				i2c_stop();
				base_hdmi_b = hdmi_b;
			}

			if (usb) {
				i2c_start();
				i2c_write_address(BASE_I2C_ADDRESS);
				i2c_write(BASE_COMMAND_SET_USB | usb);
				i2c_stop();
				base_usb = usb;
			}

			update_leds(base_hdmi_a, base_hdmi_b, base_usb);
		}
	}

	/*
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
	*/

	return 0;
}