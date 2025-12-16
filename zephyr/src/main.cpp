#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>

#include "uart.h"
#include "frames.h"


//uint8_t buffer[MAX_BUFFER] = {0,1,2,3,4,5};

//K_THREAD_DEFINE(ping_thread, 1024, pinging, NULL, NULL, NULL,
//                5, 0, 0);
//K_THREAD_DEFINE(uart_listen_thread, 1024, uart_listen, NULL, NULL, NULL,
//                6, 0, 0);

int main()
{
    //send boot message


    k_msleep(250);
    uart_init();

    //printf("hij pingt\n");
    k_msleep(666);
    //printf("en het programma gaat ongestoord verder\n");

    // SEND BOOT MESSAGE
    BootFrame Boot(NULL, MAX_BUFFER);
    Boot.structToBitstream(tx_buffer);

    return 0;
}
