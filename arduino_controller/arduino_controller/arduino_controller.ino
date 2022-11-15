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

// software serial pins
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
  if (rpi_receiver.available() > 0) {
     int cmd = rpi_receiver.read();
     int ch = cmd/3;
     int v = cmd%3; 
     switch(v) {
      case 0:
        sbusSIGNAL[ch] = BW;
        break;
      case 1:
        sbusSIGNAL[ch] = STOP;
        break;
      case 2:
<<<<<<< Updated upstream
        sbusSIGNAL[0] = FW; 
        break;
     }
=======
        sbusSIGNAL[ch] = FW; 
        break;
     }
  }
>>>>>>> Stashed changes
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
