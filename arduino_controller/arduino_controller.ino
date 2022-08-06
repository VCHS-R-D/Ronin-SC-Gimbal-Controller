#include "BMC_SBUS.h"

// channels
#define PAN_CH 1
#define TILT_CH 2
#define ROLL_CH 4

//Declare BMC_SBUS Object
BMC_SBUS mySBUS;

const int sbusWAIT = 7; //frame timing delay in msecs

void setup() {
  // Start BMC_SBUS object

  mySBUS.begin();

}

void loop() {

    //Map wiichuck values which go from 0-255 to Sbus values 0-2047
    // For no move send 1023
    int tiltValue = map(20,0,255,0,2047);

    // Set sbus tilt
    mySBUS.Servo(TILT_CH,tiltValue);

    // Check if trigger(button Z) is pressed, if so send the X value to roll channel
   
    // Update SBUS object and send data
    mySBUS.Update();
    mySBUS.Send();
    // Delay for SBUS
    delay(sbusWAIT);
    

}
