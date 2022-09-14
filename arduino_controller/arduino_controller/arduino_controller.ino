#include "BMC_SBUS.h"
#include <arduino-timer.h>
#include <SoftwareSerial.h>

enum Direction {
  FORWARD,
  REVERSE
};

// channels
#define PAN_CH 1
#define TILT_CH 2
#define ROLL_CH 4
#define STOP 1023 

// pins
#define RX 2
#define TX 3

//Declare BMC_SBUS Object
BMC_SBUS mySBUS;
SoftwareSerial rpi_receiver (RX, TX);


const int sbusWAIT = 7; //frame timing delay in msecs
const int reverseSPEED = 2047-400;
const int forwardSPEED = 500;
int sbusSIGNAL = STOP;

Timer<3> scheduler;

void read_serial(void) {
  if (rpi_receiver.available() > 0) {
     int r = rpi_receiver.read();
     
     if (r == 1) sbusSIGNAL = forwardSPEED;
     else if (r == 2) sbusSIGNAL = reverseSPEED;
     else sbusSIGNAL = STOP;
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
  // Start sofware serial
  rpi_receiver.begin(9600);
  // schedule recurrent tasks and ROUTINES
  scheduler.every(sbusWAIT, motor_controller);
}

void loop() {
  scheduler.tick();
  read_serial();
}
