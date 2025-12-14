#include <Arduino.h>
#line 1 "/home/bianca/Repos/UART_program/arduino/ARDUINO_UART/ARDUINO_UART.ino"
//define STX 0x02//!!
//define ETX 0x03//!!

#include <PLATFORM_HAL.h>
#include <uart.h>
#include <frames.h>

  //#define MAX_BUFFER 128//!!
  //int i = 0;  
  //int inFrame = 0;

#line 12 "/home/bianca/Repos/UART_program/arduino/ARDUINO_UART/ARDUINO_UART.ino"
void setup();
#line 23 "/home/bianca/Repos/UART_program/arduino/ARDUINO_UART/ARDUINO_UART.ino"
void loop();
#line 12 "/home/bianca/Repos/UART_program/arduino/ARDUINO_UART/ARDUINO_UART.ino"
void setup() {
    delay(1500);
    uart_init();
    hal_print("heh-lo\n");
    //Serial.begin(115200);   // Open seriële communicatie op 115200 baud
    //uart_init();
    //uart_listen();
    //Serial.println("hallo");
  // SEND BOOT MESSAGE
}

void loop() {

  // PING THREAD
  //pinging();
  // LISTEN THREAD

  // ASK VALUES
}

