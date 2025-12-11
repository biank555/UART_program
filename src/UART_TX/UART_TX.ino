/*
 */
#include "/home/bianca/Repos/UART/src/uart.h"

void setup() {
  Serial.begin(115200);
  delay(2000);   // geef de bootloader tijd bij volgende upload
}

void loop() {
  Serial.println(BUF_SIZE);
  Serial.println("Hello from Arduino Uno!!\n");
  delay(2000);
}
