#include "stm8/registers.h"

void uart_init() {
	*UART1_BRR1 = 0x11;
	*UART1_BRR2 = 0x06;
}