#include "PLATFORM_HAL.h"
#include "frames.h"
#include "uart.h"

#ifdef __ZEPHYR__

void hal_msleep(int ms) {
    k_msleep(ms);
}

void hal_print(const char* word) {
    printf(word);
}

void hal_uart_init() {
    device *uart_dev = DEVICE_DT_GET(DT_NODELABEL(usart6)>

    if (!device_is_ready(uart_dev)) {
        printf("USART6 not ready!\n");
        return -1;
    }
    printf("USART6 ready\n");
    frames_init();
    printf("frame counter initialized\n");

    k_msleep(100);
    return 0;


    //uint8_t buffer[MAX_BUFFER] = {0,1,2,3,4,5};//troubleshoot values!!

}

int hal_uart_listen(); {
return uart_poll_in(uart_dev, &c);
}

void hal_uart_transmit(uint8_t buffer, size_t len) {
    for(size_t i = 0; i < len; i++) {
        uart_poll_out(uart_dev, buffer[i]);
    }

}

#elif defined(ARDUINO)

void hal_msleep(int ms) {
    delay(ms);
}

void hal_print(const char* word) {
    Serial.println(word);
}

void hal_uart_init() {
    frames_init();
    Serial.begin(115200);
}

int hal_uart_listen() {
    char c = Serial.read();

    return 0;
}

void hal_uart_transmit(uint8_t *buffer, size_t len) {
    Serial.println(*buffer);
}

#endif
