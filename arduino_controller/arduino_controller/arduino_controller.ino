#include "BMC_SBUS.h"
#include <arduino-timer.h>


enum Direction {
  FORWARD,
  REVERSE
};

// channels
#define PAN_CH 1
#define TILT_CH 2
#define ROLL_CH 4
#define STOP 1023 

//Declare BMC_SBUS Object
BMC_SBUS mySBUS;

const int sbusWAIT = 7; //frame timing delay in msecs
const int reverseSPEED = 2047-400;
const int forwardSPEED = 500;
int sbusSIGNAL = forwardSPEED;

Timer<3> scheduler;

void read_serial(void) {
  if (Serial.available() > 0) {
     r = Serial.read();
     
     if (r == 1) sbusSIGNAL = forwardSPEED;
     else if (r == 2) sbusSIGNAL = reverseSPEED;
  }
}

void stop_action(void) {
  sbusSIGNAL = STOP;
}

void motor_controller(void) {
    // Set sbus tilt

    mySBUS.Servo(PAN_CH, sbusSIGNAL);
   
    // Update SBUS object and send data
    mySBUS.Update();
    mySBUS.Send();
    
}

void setup() {
  // Start BMC_SBUS object
  mySBUS.begin();
  scheduler.every(sbusWAIT, motor_controller);
  scheduler.every(1, read_serial);
//  scheduler.at(7000, stop_action);
}

void loop() {
  scheduler.tick();
}
