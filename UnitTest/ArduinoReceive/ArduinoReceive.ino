#include <SoftwareSerial.h>

#define RX 3
#define TX 4

SoftwareSerial rpi_receiver (RX, TX);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  rpi_receiver.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (rpi_receiver.available() > 0) {
    int r = rpi_receiver.read()-'0'; 
    Serial.println(r);
  }
}A
