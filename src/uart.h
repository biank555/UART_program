#ifndef UART_H
#define UART_H

#define BUF_SIZE 128
#define STX 0x02
#define ETX 0x03

void uart_receive(void* dev);
void uart_send(void* dev);


#endif // UART_H
