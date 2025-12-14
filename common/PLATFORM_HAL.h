#ifndef PLATFORM_HAL_H
#define PLATFORM_HAL_H

#include "stdint.h"

#ifdef __ZEPHYR__
#include  <zephyr/device.h>
static const struct device *uart_dev;
#elif defined(ARDUINO)
#include <Arduino.h>
typedef unsigned char uint8_t;
#endif

void hal_msleep(int ms);

char hal_buffer;

void hal_uart_init();
int hal_uart_listen();
void hal_uart_transmit(uint8_t *buffer, size_t len);

#endif // PLATFORM_HAL_H
