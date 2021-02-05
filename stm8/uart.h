#ifndef _STM8_UART_H
#define _STM8_UART_H

void uart_init();
void uart_write_byte(char c);
void uart_write_string(char * s);

#endif