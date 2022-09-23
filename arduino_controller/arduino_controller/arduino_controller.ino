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
#define RX 3
#define TX 4
//time
#define sbusWAIT 7

//Declare BMC_SBUS Object
BMC_SBUS mySBUS;
SoftwareSerial rpi_receiver (RX, TX);

int sbusSIGNAL[3];

Timer<3> scheduler;

void read_serial(void) {
//  sbusSIGNAL = STOP;
  if (rpi_receiver.available() > 0) {
    // read as char 
     int r = rpi_receiver.read()-'0'; 
     switch(r) {
      case 0:
        sbusSIGNAL[0] = STOP;
        sbusSIGNAL[1] = STOP;
        sbusSIGNAL[2] = STOP;
        break;
      case 1:
        sbusSIGNAL[0] = FW;
        break;
      case 2:
        sbusSIGNAL[0] = BW; 
        break;
      case 3:
        sbusSIGNAL[1] = FW;
        break;
      case 4:
        sbusSIGNAL[1] = BW;
        break;
      case 5:
        sbusSIGNAL[2] = FW;
        break;
      case 6:
        sbusSIGNAL[2] = BW;
        break; 
     }
     
}

void motor_controller(void) {
    // Set sbus tilt
    mySBUS.Servo(PAN_CH, sbusSIGNAL[0]);
    mySBUS.Servo(TILT_CH, sbusSIGNAL[1]);
    mySBUS.Servo(ROLL_CH, sbusSIGNAL[2]);

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
