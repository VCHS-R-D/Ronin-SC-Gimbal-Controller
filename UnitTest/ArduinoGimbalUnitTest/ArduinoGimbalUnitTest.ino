#include "BMC_SBUS.h"
#include <arduino-timer.h>
#include <SoftwareSerial.h>

// channels
#define PAN_CH 1
#define TILT_CH 2
#define ROLL_CH 4

// sig
#define STOP 1023 
#define FW 500
#define BW 1647

// pins
#define RX 2
#define TX 3

//time
#define sbusWAIT 7

//Declare BMC_SBUS Object
BMC_SBUS mySBUS;

Timer<3> scheduler;

void motor_controller(void) {
    mySBUS.Servo(PAN_CH, FW);

    // Update SBUS object and send data
    mySBUS.Update();
    mySBUS.Send();
}

void setup() {
  // Start BMC_SBUS object
  mySBUS.begin();
  // schedule recurrent tasks and ROUTINES
  scheduler.every(sbusWAIT, motor_controller);
}

void loop() {
  scheduler.tick();
}
