#include "PLATFORM_HAL.h"
#include "uart.h"

#include "frames.h"

#ifdef __ZEPHYR__
#include <zephyr/drivers/uart.h>
#include <zephyr/kernel.h>
#endif


uint8_t tx_buffer[MAX_BUFFER];
uint8_t rx_buffer[MAX_BUFFER];

// INITIALIZER
int uart_init() {

    if(hal_uart_init() != 0 ) {//TODO:fix whatever this is!!
        hal_print("UART not ready!\n");
	return 1;
    }
    hal_print("UART ready\n");
    frame_id_init();
    //send boot message

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

    //hal_print("UART: Listening...\n");//!!

    int inFrame = 0;

    size_t i = 0;
    uint8_t c;

    while(1) {
        if (hal_uart_listen(&c) == 0) {
	    printf("hal_uart_listen: c = %x\n",c);

            if (c == STX) {
		i = 0;
		rx_buffer[i] = c;
                inFrame = 1;

            } else if (inFrame) {

		if (i<MAX_BUFFER) {
    		    rx_buffer[i++] = c;
		} else {
		    inFrame = 0;
		    i = 0;
		}

		if (c == ETX) {
		    printf("ETX seen\n");
		    rx_buffer[i++];
		    inFrame = 0;
		    Frame::readFrame(rx_buffer);
		    i = 0;
		}
	    }
        }
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

void uart_transmit(uint8_t *tx_buffer, size_t len)
{
    printf("in uart_transmit \n");
    for(size_t i = 0; i < len; i++) {
	printf("[%d]%x  ", i, tx_buffer[i]);
	//hal_uart_transmit(&tx_buffer[i]);
    }
    hal_print("\n");

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
