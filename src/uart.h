#ifndef UART_H
#define UART_H

#define BUF_SIZE 128
#define STX 0x02
#define ETX 0x03

#ifdef __ZEPHYR__
int device_init();
void uart_receive();
void uart_send();
#endif // __ZEPHYR__

#endif // UART_H
