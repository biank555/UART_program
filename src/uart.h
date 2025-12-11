#ifndef UART_H
#define UART_H

#define BUF_SIZE 128
#define STX 0x02
#define ETX 0x03

#ifdef __ZEPHYR__
#include <zephyr/device.h>
#include <zephyr/kernel.h>
void uart_receive(const device *dev);
void uart_send(const device *dev);
#endif // __ZEPHYR__

#endif // UART_H
