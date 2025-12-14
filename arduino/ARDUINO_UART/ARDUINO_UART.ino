//define STX 0x02//!!
//define ETX 0x03//!!

#include "PLATFORM_HAL.h"
#include "uart.h"
#include "frames.h"

  //#define MAX_BUFFER 128//!!
  //char buffer[MAX_BUFFER];
  //int i = 0;  
  //int inFrame = 0;

void setup() {
  //Serial.begin(115200);   // Open seriële communicatie op 115200 baud
    uart_init();
    uart_listen();
  //Serial.println(STX);
  // SEND BOOT MESSAGE
}

void loop() {

  // PING THREAD
  //pinging();
  // LISTEN THREAD

  // ASK VALUES
}
