#ifndef _STM8_REGISTERS_H
#define _STM8_REGISTERS_H

#include <stdint.h>

#define reg8(x) ((volatile uint8_t *) x)

/*
 * I/O ports
 */
#define PA_BASE 0x005000
#define PA_ODR reg8(PA_BASE + 0x00)
#define PA_IDR reg8(PA_BASE + 0x01)
#define PA_DDR reg8(PA_BASE + 0x02)
#define PA_CR1 reg8(PA_BASE + 0x03)
#define PA_CR2 reg8(PA_BASE + 0x04)

#define PB_BASE 0x005005
#define PB_ODR reg8(PB_BASE + 0x00)
#define PB_IDR reg8(PB_BASE + 0x01)
#define PB_DDR reg8(PB_BASE + 0x02)
#define PB_CR1 reg8(PB_BASE + 0x03)
#define PB_CR2 reg8(PB_BASE + 0x04)

#define PC_BASE 0x00500A
#define PC_ODR reg8(PC_BASE + 0x00)
#define PC_IDR reg8(PC_BASE + 0x01)
#define PC_DDR reg8(PC_BASE + 0x02)
#define PC_CR1 reg8(PC_BASE + 0x03)
#define PC_CR2 reg8(PC_BASE + 0x04)

#define PD_BASE 0x00500F
#define PD_ODR reg8(PD_BASE + 0x00)
#define PD_IDR reg8(PD_BASE + 0x01)
#define PD_DDR reg8(PD_BASE + 0x02)
#define PD_CR1 reg8(PD_BASE + 0x03)
#define PD_CR2 reg8(PD_BASE + 0x04)

#define PE_BASE 0x005014
#define PE_ODR reg8(PE_BASE + 0x00)
#define PE_IDR reg8(PE_BASE + 0x01)
#define PE_DDR reg8(PE_BASE + 0x02)
#define PE_CR1 reg8(PE_BASE + 0x03)
#define PE_CR2 reg8(PE_BASE + 0x04)

#define PF_BASE 0x005019
#define PF_ODR reg8(PF_BASE + 0x00)
#define PF_IDR reg8(PF_BASE + 0x01)
#define PF_DDR reg8(PF_BASE + 0x02)
#define PF_CR1 reg8(PF_BASE + 0x03)
#define PF_CR2 reg8(PF_BASE + 0x04)

/*
 * CLK
 */
#define CLK_BASE 0x0050C0
#define CLK_ICKR reg8(CLK_BASE + 0x00)
#define CLK_ECKR reg8(CLK_BASE + 0x01)
// reserved area (1 byte)
#define CLK_CMSR reg8(CLK_BASE + 0x03)
#define CLK_SWR reg8(CLK_BASE + 0x04)
#define CLK_SWCR reg8(CLK_BASE + 0x05)
#define CLK_CKDIVR reg8(CLK_BASE + 0x06)
#define CLK_PCKENR1 reg8(CLK_BASE + 0x07)
#define CLK_CSSR reg8(CLK_BASE + 0x08)
#define CLK_CCOR reg8(CLK_BASE + 0x09)
#define CLK_PCKENR2 reg8(CLK_BASE + 0x0A)
// reserved area (1 byte)
#define CLK_HSITRIMR reg8(CLK_BASE + 0x0C)
#define CLK_SWIMCCR reg8(CLK_BASE + 0x0D)

/*
 * UART1
 */
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

/*
 * UART flags
 */
#define UART_SR_TXE (1 << 7)
#define UART_SR_TC (1 << 6)
#define UART_SR_RXNE (1 << 5)
#define UART_SR_IDLE (1 << 4)
#define UART_SR_OR (1 << 3)
#define UART_SR_NF (1 << 2)
#define UART_SR_FE (1 << 1)
#define UART_SR_PE (1 << 0)

#define UART_CR2_TIEN (1 << 7)
#define UART_CR2_TCIEN (1 << 6)
#define UART_CR2_RIEN (1 << 5)
#define UART_CR2_ILIEN (1 << 4)
#define UART_CR2_TEN (1 << 3)
#define UART_CR2_REN (1 << 2)
#define UART_CR2_RWU (1 << 1)
#define UART_CR2_SBK (1 << 0)

#endif