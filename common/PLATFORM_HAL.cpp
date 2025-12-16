#include "PLATFORM_HAL.h"
#include "frames.h"
#include "uart.h"

#ifdef __ZEPHYR__

void hal_msleep(int ms) {
    k_msleep(ms);
    return;
}

int hal_print(const char* str) {

    for (size_t i = 0; i < MAX_BUFFER; i++) {
        printk("%02X ", str[i]);
    }
    printk("\n");

    return 0;
}

int hal_uart_init() {
    const device *uart_dev = DEVICE_DT_GET(DT_NODELABEL(usart6));

    if (!device_is_ready(uart_dev)) {
        printf("USART6 not ready!\n");
	return 1;
    }
    printf("USART6 ready\n");
    printf("frame counter initialized\n");

    k_msleep(100);


    //uint8_t buffer[MAX_BUFFER] = {0,1,2,3,4,5};//troubleshoot values!!
    return 0;
}

int hal_uart_listen(uint8_t *c) {
return uart_poll_in(uart_dev, c);
}

int hal_uart_transmit(uint8_t *c) {
    uart_poll_out(uart_dev, *c);
    //hal_print(["hal_uart_transmit_buffer = %x", buffer[i];
    return 0;
}

#elif defined(ARDUINO)

void hal_msleep(int ms) {
    delay(ms);
    return;
}

int hal_print(const char* word) {
    Serial.println(word);
    return 0;
}

int hal_uart_init() {
    hal_print("in hal_uart_init\n");
    Serial.begin(115200);
    //Serial.println("hal_uart_init Serial.begun\n");//!!
    return 0;
}

int hal_uart_listen(uint8_t *c) {

    if(Serial.available() == 0) {
	return -1;
    }

    char character = (uint8_t)Serial.read();
    if (character < 0) {
	return -1;
    }
    *c = (uint8_t)character;
    return 0;
}

int hal_uart_transmit(uint8_t *c) {
    Serial.println(*c);
    return 0;
}

#endif
