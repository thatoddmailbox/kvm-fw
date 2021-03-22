#include "stm8/i2cbb.h"
#include "stm8/registers.h"
#include "stm8/timer.h"

// there are two i2c ports that we are interested in bitbanging
// HDMI A - PC6/SCL and PC7/SDA
// HDMI B - PC4/SCL and PC5/SDA
// they are both on port C
// there's also nothing else on port C, so we can assume full control over it

#define I2CBB_A_SCL 4
#define I2CBB_A_SDA 5
#define I2CBB_B_SCL 6
#define I2CBB_B_SDA 7

// aliases to gpio registers for port C
#define I2CBB_ODR 0x00500A
#define I2CBB_IDR 0x00500B
#define I2CBB_DDR 0x00500C
#define I2CBB_CR1 0x00500D
#define I2CBB_CR2 0x00500E

// see https://stackoverflow.com/questions/40591312/c-macro-how-to-get-an-integer-value-into-a-string-literal
#define STR_IMPL_(x) #x
#define STR(x) STR_IMPL_(x)

#define A_IN() __asm__("bres " STR(I2CBB_DDR) ", #" STR(I2CBB_A_SDA));
#define A_OUT() __asm__("bset " STR(I2CBB_DDR) ", #" STR(I2CBB_A_SDA));
#define A_SDA_HIGH() __asm__("bset " STR(I2CBB_ODR) ", #" STR(I2CBB_A_SDA));
#define A_SCL_HIGH() __asm__("bset " STR(I2CBB_ODR) ", #" STR(I2CBB_A_SCL));
#define A_SDA_LOW() __asm__("bres " STR(I2CBB_ODR) ", #" STR(I2CBB_A_SDA));
#define A_SCL_LOW() __asm__("bres " STR(I2CBB_ODR) ", #" STR(I2CBB_A_SCL));
#define A_SDA_READ() ((*reg8(I2CBB_IDR) & (1 << I2CBB_A_SDA)) != 0)

// we're running at 25 kHz, meaning a clock period of 40 us
#define WAIT_PERIOD() timer_delay_us(40)
#define WAIT_HALF_PERIOD() timer_delay_us(20)
#define WAIT_QUARTER_PERIOD() timer_delay_us(10)

void i2cbb_init() {
	A_SDA_HIGH();
	A_SCL_HIGH();

	// we are always in control of SCL
	__asm__("bset " STR(I2CBB_DDR) ", #" STR(I2CBB_A_SCL));
	A_OUT();
}

void i2cbb_start() {
	A_SDA_HIGH();
	A_SCL_HIGH();
	A_OUT();
	WAIT_PERIOD();
	A_SDA_LOW();
	WAIT_PERIOD();
	A_SCL_LOW();
	WAIT_PERIOD();
}

void i2cbb_stop() {
	A_OUT();
	A_SDA_LOW();
	A_SCL_LOW();
	WAIT_PERIOD();
	A_SCL_HIGH();
	WAIT_PERIOD();
	A_SDA_HIGH();
	WAIT_PERIOD();
}

void i2cbb_bit(bool bit) {
	if (bit) {
		A_SDA_HIGH();
	} else {
		A_SDA_LOW();
	}
	WAIT_HALF_PERIOD();
	A_SCL_HIGH();
	WAIT_HALF_PERIOD();
	A_SCL_LOW();
}

uint8_t i2cbb_read() {
	A_IN();

	uint8_t data = 0;
	for (uint8_t i = 0; i < 8; i++)
	{
		A_SCL_LOW();
		WAIT_HALF_PERIOD();
		A_SCL_HIGH();
		WAIT_QUARTER_PERIOD();
		data = data << 1;
		if (A_SDA_READ()) {
			data += 1;
		}
		WAIT_QUARTER_PERIOD();
	}

	A_OUT();
	A_SCL_LOW();
	i2cbb_bit(true);

	return data;
}

bool i2cbb_write(uint8_t data) {
	A_SCL_LOW();
	A_OUT();

	for (uint8_t i = 8; i > 0; i--) {
		i2cbb_bit(data & (1 << (i - 1)));
	}

	A_IN();
	WAIT_HALF_PERIOD();
	A_SCL_HIGH();
	bool nack = A_SDA_READ();
	WAIT_HALF_PERIOD();

	// before the falling edge of SCL, we repeat the ack/nack bit we just read to SDA
	// this is because once SCL goes low, the chip we're talking to floats SDA, and we still have it as an input
	// so it would get pulled high and then immediately set low on our next write, causing a blip
	// the blip doesn't really interfere with anything, since no one tries to read at that time
	// so doing this is somewhat extra/perfectionist
	// see github issue #1 for more details
	if (nack) {
		A_SDA_HIGH();
	} else {
		A_SDA_LOW();
	}
	A_OUT();

	A_SCL_LOW();
	return !nack;
}