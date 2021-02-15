#include "base/fsusb74.h"
#include "stm8/registers.h"

#define FSUSB74_PORT PD
#define FSUSB74_PIN_nOE 2
#define FSUSB74_PIN_SEL0 3
#define FSUSB74_PIN_SEL1 4

#define FSUSB74_PORT_REGISTER(x) FSUSB74_PORT_REGISTER__(FSUSB74_PORT, x)
#define FSUSB74_PORT_REGISTER_(x, y) x ## _ ## y
#define FSUSB74_PORT_REGISTER__(x, y) FSUSB74_PORT_REGISTER_(x, y)

void fsusb74_init() {
	// all pins output
	*FSUSB74_PORT_REGISTER(DDR) |= (1 << FSUSB74_PIN_nOE) | (1 << FSUSB74_PIN_SEL0) | (1 << FSUSB74_PIN_SEL1);

	// enable output, default to port 0
	*FSUSB74_PORT_REGISTER(ODR) &= ~((1 << FSUSB74_PIN_nOE) | (1 << FSUSB74_PIN_SEL0) | (1 << FSUSB74_PIN_SEL1));
}

void fsusb74_select_port(uint8_t index) {
	// TODO: use bset/bres instructions? would it help with code size?
	if ((index & 0x2) != 0) {
		// set sel1
		*FSUSB74_PORT_REGISTER(ODR) |= (1 << FSUSB74_PIN_SEL1);
	} else {
		// clear sel1
		*FSUSB74_PORT_REGISTER(ODR) &= ~(1 << FSUSB74_PIN_SEL1);
	}

	if ((index & 0x1) != 0) {
		// set sel0
		*FSUSB74_PORT_REGISTER(ODR) |= (1 << FSUSB74_PIN_SEL0);
	} else {
		// clear sel0
		*FSUSB74_PORT_REGISTER(ODR) &= ~(1 << FSUSB74_PIN_SEL0);
	}
}