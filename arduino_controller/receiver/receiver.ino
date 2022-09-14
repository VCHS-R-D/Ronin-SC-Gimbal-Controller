#include <SoftwareSerial.h>


SoftwareSerial mySerial(3, 4);

void setup() {
    pinMode(3, INPUT);
    pinMode(4, OUTPUT);
    
    mySerial.begin(9600);
    Serial.begin(9600);
}

void loop() {
//  Serial.println(mySerial.available());
  if (mySerial.available() > 0) {
    Serial.println(mySerial.read());
  }
}
