
#include "uart.h"
#include "frames.h"

#include <zephyr/drivers/uart.h>
#include <zephyr/kernel.h>

const struct device *uart_dev = DEVICE_DT_GET(DT_NODELABEL(usart6));

int device_init() {
    if (!device_is_ready(uart_dev)) {
        printk("USART6 not ready!\n");
        return -1;
    }
    printk("USART6 ready\n");
    //k_msleep(2000);
    return 0;
}

void uart_receive()
{
    printk("reading Arduino...\n");

    char buffer[BUF_SIZE];
    int i = 0;
    unsigned char c;

    while (1) {
        if (uart_poll_in(uart_dev, &c) == 0) {
            if (c == '\n' || i >= BUF_SIZE - 1) {
                buffer[i] = '\0';
                printk("%s\n", buffer);
                i = 0;
            } else if (c != '\r') {
                buffer[i++] = c;
            }
        }
    }

}

void uart_send()
{

/*
    printk("sending to Arduino...\n");

    char buffer[BUF_SIZE];
    int i = 0;
    char msg[]  = {"\x02Hello from stm32f746g Discovery\x03"};

    while(1) {
        printk("%c \t {%x}\n",msg[i], msg[i]);
        if (i >= sizeof(msg) || i >= BUF_SIZE-1) {
            i = 0;
            k_msleep(2000);
        } else {
            uart_poll_out(uart_dev, msg[i++]);
        }
    }
*/
}
