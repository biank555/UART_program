#ifndef UART_H
#define UART_H

#define MAX_BUFFER 128
#define STX 0x02
#define ETX 0x03

#ifdef __ZEPHYR__
#include <zephyr/kernel.h>
     //only zephyr
#endif // __ZEPHYR__

extern uint8_t *buffer[MAX_BUFFER];


int uart_init();
void uart_listen();
//void print();
void uart_transmit(uint8_t *buffer, size_t len);
void read_frame(uint8_t *buffer, size_t len);
void pinging();

#endif // UART_H
