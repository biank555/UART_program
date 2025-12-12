#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/sys/printk.h>

#include "uart.h"
#include "frames.h"

struct uart_config cfg = {
    .baudrate = 115200,
    .parity = UART_CFG_PARITY_NONE,
    .stop_bits = UART_CFG_STOP_BITS_1,
    .data_bits = UART_CFG_DATA_BITS_8,
    .flow_ctrl = UART_CFG_FLOW_CTRL_NONE
};

uint8_t buffer[BUF_SIZE];

int main()
{
    device_init();

    //uart_receive(uart_dev);
    //uart_send(uart_dev);


    //make ACK
    //AckFrame Ack;
    //Ack.serialize(buffer);
    for(int i = 0; i<6 ;i++) {
        printk("buffer[%d] = %x\n",i , buffer[i]);
    }
    //serialize
    //send ACK



    return 0;
}
