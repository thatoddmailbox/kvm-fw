#ifndef _STM8_REGISTERS_H
#define _STM8_REGISTERS_H

#include <stdint.h>

#define reg8(x) ((volatile uint8_t *) x)

#define UART1_BASE 0x005230
#define UART1_SR reg8(UART1_BASE + 0x00)
#define UART1_DR reg8(UART1_BASE + 0x01)
#define UART1_BRR1 reg8(UART1_BASE + 0x02)
#define UART1_BRR2 reg8(UART1_BASE + 0x03)
#define UART1_CR1 reg8(UART1_BASE + 0x04)
#define UART1_CR2 reg8(UART1_BASE + 0x05)
#define UART1_CR3 reg8(UART1_BASE + 0x06)
#define UART1_CR4 reg8(UART1_BASE + 0x07)
#define UART1_CR5 reg8(UART1_BASE + 0x08)
// note that the following registers are specific to UART1 -- other UARTs have different registers
#define UART1_GTR reg8(UART1_BASE + 0x09)
#define UART1_PSCR reg8(UART1_BASE + 0x0A)

#define UART_SR_TXE (1 << 7)
#define UART_SR_TC (1 << 6)
#define UART_SR_RXNE (1 << 5)
#define UART_SR_IDLE (1 << 4)
#define UART_SR_OR (1 << 3)
#define UART_SR_NF (1 << 2)
#define UART_SR_FE (1 << 1)
#define UART_SR_PE (1 << 0)

#endif