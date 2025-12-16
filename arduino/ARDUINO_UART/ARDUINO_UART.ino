//define STX 0x02//!!
//define ETX 0x03//!!

#include <PLATFORM_HAL.h>
#include <uart.h>
#include <frames.h>

  //#define MAX_BUFFER 128//!!
  //int i = 0;  
  //int inFrame = 0;

void setup() {
    delay(1500);
    uart_init();
    hal_print("henlo\n");

    uint8_t msg[32] = "is deze boot msg leesbaar?";
    Serial.println(sizeof(msg));
    BootFrame Boot(msg, sizeof(msg));
    Boot.structToBitstream(*buffer);
    uart_transmit(buffer, sizeof(buffer));

    //Serial.println("hallo");
  // SEND BOOT MESSAGE
}

void loop() {

    // PING THREAD
    //pinging();

    // LISTEN THREAD
    //uart_listen();
    
    // ASK VALUES
}
