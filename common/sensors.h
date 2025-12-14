#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>

enum SensorType {
    TEMP,
    SDCARD,
    BUTTON
};

int readSensor(SensorType sensor, uint8_t *data);

int getTemp(uint8_t *temperature);
int detectSD(uint8_t *cardDetected);
int getButton(uint8_t *pushed);

#endif // UART_H
