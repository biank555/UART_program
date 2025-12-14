#include "PLATFORM_HAL.h"
#include "uart.h"

#include "frames.h"

#ifdef __ZEPHYR__
#include <zephyr/drivers/uart.h>
#include <zephyr/kernel.h>
#endif


uint8_t buffer[MAX_BUFFER];


// INITIALIZER
int uart_init() {
    hal_uart_init();//TODO:fix whatever's going on here!!
    return 0;
}


// THREADS

void pinging() {
    //PingFrame ping(buffer,6);
    //ping.structToBitstream(buffer);
    for (int i = 0; i<6; i++) {
        //printf("buffer[%d] = %d\n", i, buffer[i]);

    //k_msleep(1500);
    }
    //TODO:timeout counter!!
    //TODO:if time-out: resend n times
    //TODO:after n times: restart other
}


void uart_listen()
{

    printf("UART: Listening...\n");

    int inFrame = 0;

    size_t i = 0;
    uint8_t *c;

    while(1) {
        if (hal_uart_listen(c) == 0) {

            if (*c == STX) {
		i = 0;
		buffer[i] = *c;
                inFrame = 1;

            } else if (inFrame) {

		if (i>MAX_BUFFER) {
    		    buffer[i++] = *c;
		} else {
		    inFrame = 0;
		    i = 0;
		}

		if (*c == ETX) {
		    inFrame = 0;
		    i = 0;
		    read_frame(buffer, buffer[3]);
		}
	    }


        }
    }
}


void read_frame(uint8_t *buffer, size_t len) {


    BootFrame bootFrame(buffer, len);
    ReqFrame reqFrame(buffer, len);
    DataFrame dataFrame(buffer, len);
    AckFrame ackFrame(buffer, len);
    NackFrame nackFrame(buffer, len);
    PingFrame pingFrame(buffer, len);


    switch (buffer[1]) {
	case BOOTMESSAGE:
	    bootFrame.bitstreamToStruct(buffer);
	    //send ACK
	    printf("%c",bootFrame.bootMessage);
	    break;

	case REQUEST:
	    reqFrame.bitstreamToStruct(buffer);
	    //send ACK?
	    //sensor measurements
	    dataFrame.id = reqFrame.id;
	    dataFrame.payload = reqFrame.requests;
	    break;

	case DATA:
	    dataFrame.bitstreamToStruct(buffer);
	    ackFrame.id = dataFrame.id;
	    uart_transmit(buffer,ackFrame.length); // send ACK
	    break;

	case ACK:
	    ackFrame.bitstreamToStruct(buffer);
	    //TODO!!
	    break;

	case NACK://TODO:implement!!
	    nackFrame.bitstreamToStruct(buffer);
	    break;

	case PING:
	    pingFrame.bitstreamToStruct(buffer);
            ackFrame.id = pingFrame.id;
            uart_transmit(buffer,ackFrame.length); // send ACK
	    break;
    }
}

/*
    char buffer[MAX_BUFFER];
    int i = 0;
    unsigned char c;

    while (1) {
        if (uart_poll_in(uart_dev, &c) == 0) {
            if (c == '\n' || i >= MAX_BUFFER - 1) {
                buffer[i] = '\0';
                printk("%s\n", buffer);
                i = 0;
            } else if (c != '\r') {
                buffer[i++] = c;
            }
        }
    }
*/

void uart_transmit(uint8_t *buffer, size_t len)
{
    printf("sending ...\n");

    for(size_t i = 0; i < len; i++) {
	hal_uart_transmit(buffer, sizeof(buffer));
    }

/*
    char buffer[MAX_BUFFER];
    int i = 0;
    char msg[]  = {"\x02Hello from stm32f746g Discovery\x03"};

    while(1) {
        printk("%c \t {%x}\n",msg[i], msg[i]);
        if (i >= sizeof(msg) || i >= MAX_BUFFER-1) {
            i = 0;
            k_msleep(2000);
        } else {
            uart_poll_out(uart_dev, msg[i++]);
        }
    }
*/
}
