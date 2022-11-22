# Project Goals
Controlling the Ronin SC Gimbal with:
* Directly from a Raspberry Pi (in progress)
* Arduino (done)
* Roboquest ROS System on a Raspberry Pi (done)

# Arduino Quick Start
1. Download library from source: https://github.com/boldstelvis/BMC_SBUS
2. Extract the subdirectory "BMC_SBUS", not the whole repo, into the Arduino/libraries folder
3. Use arduino_controller.ino file in arduino_controller and upload the code to the arduino
4. Run the keyboard.py input code on a raspberry pi

# ROS Quick Start
1. Flash RPI OS with roboquest software system (only available to VCHS)
2. copy and paste gimbal.py to your main package
3. Go to the Robot Dashboard Site
4. Create a Joystick that publishes to topic /gimbal
