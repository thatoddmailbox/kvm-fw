#include "stm8/uart.h"
#include "stm8/registers.h"

void uart_init() {
	// uart1 tx is pd5; uart1 rx is pd6

	*PD_DDR |= (1 << 5); // set uart1 tx to output
	*PD_CR1 |= (1 << 5); // set uart1 tx to push-pull
	*PD_DDR &= ~(1 << 6); // set uart1 rx to input
	*PD_CR1 &= ~(1 << 6); // set uart1 rx to float

	// set baud rate - 57600 @ 16 MHz
	*UART1_BRR1 = 0x11;
	*UART1_BRR2 = 0x06;

	// enable transmission
	*UART1_CR2 = UART_CR2_TEN;
}

void uart_write_byte(char c) {
	// wait for TXE flag
	while ((*UART1_SR & UART_SR_TXE) == 0) {}

	// send byte
	*UART1_DR = c;
}

void uart_write_string(char * s) {
	while (*s) {
		uart_write_byte(*s);
		s++;
	}
}