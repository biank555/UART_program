#define STX 0x02
#define ETX 0x03

#include "/home/bianca/Repos/UART/src/uart.h"
//#include "/home/bianca/Repos/UART/src/frames.h"

  char buffer[BUF_SIZE];
  int i = 0;  
  int inFrame = 0;

void setup() {
  Serial.begin(115200);   // Open seriële communicatie op 115200 baud
}

void receive() {
  char c = Serial.read();
  if (!inFrame) {
    if (c == STX) { //start of frame
      inFrame = 1;
      i = 0;
    }
  } else {
    if (c == ETX || i >= BUF_SIZE-1) { //end of frame
      i = 0;
      inFrame = 0;
      Serial.println(buffer);
    } else {
      buffer[i++] = c;
    }
  }
};


void loop() {

  while (Serial.available() > 0) {

    receive();
    //char c = Serial.read();  // 

/*    
    Serial.print("c = "); Serial.print(c); 
    Serial.print(" ("); Serial.print((int)c); Serial.print(")\t");
    Serial.print("inFrame = "); Serial.print(inFrame); Serial.print("\t");
    Serial.print("i = "); Serial.println(i);
    Serial.print("\n");
    Serial.print("\n");
*/
/*
    if (!inFrame) {
      if (c == STX) { //start of frame
        inFrame = 1;
        i = 0;
      }
    } else {
      if (c == ETX || i >= BUF_SIZE-1) { //end of frame
        i = 0;
        inFrame = 0;
        Serial.println(buffer);
      } else {
        buffer[i++] = c;
      }
    }
*/
  }
}