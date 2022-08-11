#include "BMC_SBUS.h"
#include <arduino-timer.h>

// channels
#define PAN_CH 1
#define TILT_CH 2
#define ROLL_CH 4
#define STOP 1023 

//Declare BMC_SBUS Object
BMC_SBUS mySBUS;

const int sbusWAIT = 7; //frame timing delay in msecs
const int sbusSIGNAL = 110;

/*
 * @brief convert sbus packet values to something more readable as an argument
 * @param speed value can be from -10 to 10
 * @return sbus packet value
*/
//int speed_controller(int speed_value) {
//  if (abs(speed_value) > 10) return 0;
//  else return (speed_value, -10, 10, 0, 2047);
//}
//TODO: implement

Timer<1> timer;

int panValue = 0;

void motor_routine(void) {
    // Set sbus tilt
    mySBUS.Servo(PAN_CH, panValue);
   
    // Update SBUS object and send data
    mySBUS.Update();
    mySBUS.Send();
}

void motor_routine_back(void) {
    // Set sbus tilt
    mySBUS.Servo(PAN_CH, 2047-panValue);
    // Update SBUS object and send data
    mySBUS.Update();
    mySBUS.Send();
}
void setup() {
  // Start BMC_SBUS object
  mySBUS.begin();
}

bool dir = false;

void loop() {
  timer.tick();
  
  if (!dir && timer.ticks()%2000==0) {
    motor_routine();
    dir=!dir;
  }if (dir && timer.ticks()%2000==0) {
    motor_routine_back();
    dir=!dir;
  }
}
