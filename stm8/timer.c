#include "stm8/timer.h"
#include "stm8/registers.h"

void timer_init() {
	// disable preloading and turn off the counter
	*TIM4_CR1 = 0;

	// our fMASTER is 16 MHz (HSI)
	// prescaler of 4 means we divide by 16, so timer frequency is 1 MHz
	*TIM4_PSCR = 4;

	// no interrupts, we'll poll it
	// TODO: would it be better to use interrupts for delays?
	*TIM4_IER = 0;
}

void timer_delay_us(uint8_t time) {
	// reset counter
	*TIM4_CNTR = 0;

	// start counting
	*TIM4_CR1 |= TIM4_CR1_CEN;

	while (*TIM4_CNTR != time) {}

	// stop counting
	*TIM4_CR1 &= ~TIM4_CR1_CEN;
}