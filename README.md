# Project Goals

Controlling the Ronin SC Gimbal with:

- Directly from a Raspberry Pi (in progress)
- Arduino (done)
- Roboquest ROS System on a Raspberry Pi (done)

# Circuit

![A3712243-D438-4209-9178-647ECA8FEFBC](https://user-images.githubusercontent.com/72239682/204664864-30f8819e-2d3b-4925-a9e7-740ca83037ad.jpeg)

- A Serial inverter is used to invert the serial signal from the Arduino TX into an SBUS signal the Gimbal understands
- A Raspberry pi connects to the Arduino board from UART3 TX to pin 3 on the Arduino so that they can communicate through Software Serial
- When communicating with Serial between 2 devices, the 2 devices GND must be connected too
- Note that the circuit shows a Pihat designed by the Roboquest organization. This can also be a signal that comes from the Pi gpio uart pin. 
# Arduino Quick Start

1. Download BMC_SBUS Library

- Clone: https://github.com/boldstelvis/BMC_SBUS
- Extract folder "BMC_SBUS" (not the whole repo) into your Arduino/libraries folder

2. Upload arduino_controller.ino (in arduino_controller) to an Arduino
3. Run keyboard.py on a pi

NOTE: Install the SoftwareSerial library in Arduino IDE if necessary

# ROS Quick Start

1. Flash a Raspberry Pi with the RoboQuest OS (only available to VCHS)
2. Do all steps from Arduino Quick Start
3. Add the following line to /boot/config.txt and then reboot the Pi: ```dtoverlay=uart3```
5. Copy and paste gimbal.py into your main package
6. Go to the Robot Dashboard Site
7. Create a Joystick that publishes to the topic /transform

NOTE: you will need a Roboquest PiHat
