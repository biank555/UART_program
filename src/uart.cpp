
#include "uart.h"
#include "frames.h"

#include <zephyr/drivers/uart.h>
#include <zephyr/kernel.h>

const struct device *uart_dev = DEVICE_DT_GET(DT_NODELABEL(usart6));

uint8_t buffer[MAX_BUFFER] = {0,1,2,3,4,5};//troubleshoot!!


// INITIALIZER

int uart_init() {
    if (!device_is_ready(uart_dev)) {
        printf("USART6 not ready!\n");
        return -1;
    }
    printf("USART6 ready\n");
    frames_init();
    printf("frame counter initialized\n");

    k_msleep(100);
    return 0;
}


// THREADS

void pinging() {
    while(1) {
        PingFrame ping(buffer,6);
        ping.structToBitstream(buffer);
        for (int i = 0; i<6; i++) {
            printf("buffer[%d] = %d\n", i, buffer[i]);
        }
        k_msleep(1500);
	//TODO:timeout counter!!
	//TODO:if time-out: resend n times
	//TODO:after n times: restart other
    }
}


void uart_listen()
{

    printk("UART: Listening...\n");

    uint8_t buffer[MAX_BUFFER];

    int inFrame = 0;

    size_t i = 0;
    uint8_t c;

    while(1) {
        if (uart_poll_in(uart_dev, &c) == 0) {

            if (c == STX) {
		i = 0;
		buffer[i] = c;
                inFrame = 1;

            } else if (inFrame) {

		if (i>MAX_BUFFER) {
    		    buffer[i++] = c;
		} else {
		    inFrame = 0;
		    i = 0;
		}

		if (c == ETX) {
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
	    //print bootmessage
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
	    uart_send(buffer,ackFrame.length); // send ACK
	    break;

	case ACK:
	    ackFrame.bitstreamToStruct(buffer);
	    break;

	case NACK://TODO:implement!!
	    nackFrame.bitstreamToStruct(buffer);
	    break;

	case PING:
	    pingFrame.bitstreamToStruct(buffer);
            ackFrame.id = pingFrame.id;
            uart_send(buffer,ackFrame.length); // send ACK
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

void uart_send(uint8_t *buffer, size_t len)
{
    printk("sending ...\n");

    for(size_t i = 0; i < len; i++) {
	uart_poll_out(uart_dev, buffer[i]);
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
