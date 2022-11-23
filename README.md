# Project Goals

Controlling the Ronin SC Gimbal with:

- Directly from a Raspberry Pi (in progress)
- Arduino (done)
- Roboquest ROS System on a Raspberry Pi (done)

# Circuit

![9E77B69A-0D8B-41FC-BE7E-A73A88B2DBD5](https://user-images.githubusercontent.com/72239682/203463755-5a2ced45-bd45-41da-8e0c-7f8d2f6dd1ce.jpeg)

- A Serial inverter is used to invert the serial signal from the Arduino TX into an SBUS signal the Gimbal understands
- A Raspberry pi connects to the Arduino board from UART3 TX to pin 3 on the Arduino so that they can communicate through Software Serial

# Arduino Quick Start

1. Download BMC_SBUS Library

- Clone: https://github.com/boldstelvis/BMC_SBUS
- Extract folder "BMC_SBUS" (not the whole repo) into your Arduino/libraries folder

2. Upload arduino_controller.ino (in arduino_controller) to an Arduino
3. Run keyboard.py on a pi

- remember to get the SoftwareSerial package as it is relied on for receiving key inputs from the raspberry pi

# ROS Quick Start

1. Flash RPI OS with roboquest software system (only available to VCHS)
2. Do all steps from Arduino Quick Start
3. copy and paste gimbal.py to your main package
4. Go to the Robot Dashboard Site
5. Create a Joystick that publishes to the topic /transform

- you will need the roboquest pi hat for completing the roboquest setup
