#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/sys/printk.h>

#include "uart.h"

/* Haal de USART6 device tree node */
const struct device *uart_dev = DEVICE_DT_GET(DT_NODELABEL(usart6));

struct uart_config cfg = {
    .baudrate = 115200,
    .data_bits = UART_CFG_DATA_BITS_8,
    .parity = UART_CFG_PARITY_NONE,
    .stop_bits = UART_CFG_STOP_BITS_1,
    .flow_ctrl = UART_CFG_FLOW_CTRL_NONE
};


void main(void)
{
    if (!device_is_ready(uart_dev)) {
        printk("USART6 not ready!\n");
        return;
    }

    printk("USART6 ready\n");
    k_msleep(2000);

    //uart_receive(uart_dev);
    uart_send(uart_dev);
}

