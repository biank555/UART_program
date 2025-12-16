#ifndef PLATFORM_HAL_H
#define PLATFORM_HAL_H

#include "stdint.h"

#ifdef __ZEPHYR__
#include  <zephyr/device.h>
#include <zephyr/drivers/uart.h>
static const device *uart_dev;
#elif defined(ARDUINO)
#include <Arduino.h>
typedef unsigned char uint8_t;
#endif

void hal_msleep(int ms);

//char hal_buffer;

int hal_uart_init();
int hal_print(const char* str);
int hal_uart_listen(uint8_t *c);
int hal_uart_transmit(uint8_t *c);

#endif // PLATFORM_HAL_H
