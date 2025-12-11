
#include "uart.h"
#include <zephyr/drivers/uart.h>
#include <zephyr/kernel.h>


void uart_receive(void* dev)
{
    printk("reading Arduino...\n");

    char buffer[BUF_SIZE];
    int i = 0;
    unsigned char c;

    while (1) {
        if (uart_poll_in(dev, &c) == 0) {
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

void uart_send(void* dev)
{
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
            uart_poll_out(dev, msg[i++]);
        }
    }
}
