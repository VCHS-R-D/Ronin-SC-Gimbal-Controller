#include "BMC_SBUS.h"

// channels
#define PAN_CH 1
#define TILT_CH 2
#define ROLL_CH 4

//Declare BMC_SBUS Object
BMC_SBUS mySBUS;

const int sbusWAIT = 7; //frame timing delay in msecs
const int sbusSIGNAL = 20;

/*
 * @brief convert sbus packet values to something more readable as an argument
 * @param speed value can be from -10 to 10
 * @return sbus packet value
*/
int speed_controller(int speed_value) {
  if (abs(speed_value) > 10) return 0;
  else return (speed_value, -10, 10, 0, 2047);
}

void setup() {
  // Start BMC_SBUS object
  mySBUS.begin();
}

void loop() {
    int tiltValue = map(sbusSIGNAL,0,255,0,2047);

    // Set sbus tilt
    mySBUS.Servo(PAN_CH,tiltValue);
   
    // Update SBUS object and send data
    mySBUS.Update();
    mySBUS.Send();

    // Delay for SBUS
    delay(sbusWAIT);
    

}
