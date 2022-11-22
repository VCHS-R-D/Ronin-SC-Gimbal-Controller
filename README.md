# Project Goals

Controlling the Ronin SC Gimbal with:

- Directly from a Raspberry Pi (in progress)
- Arduino (done)
- Roboquest ROS System on a Raspberry Pi (done)

# Circuit

# Arduino Quick Start

1. Download BMC_SBUS Library

- Clone: https://github.com/boldstelvis/BMC_SBUS
- Extract folder "BMC_SBUS" (not the whole repo) into your Arduino/libraries folder

2. Upload arduino_controller.ino (in arduino_controller) to an Arduino
3. Run keyboard.py on a pi

# ROS Quick Start

1. Flash RPI OS with roboquest software system (only available to VCHS)
2. Do all steps from Arduino Quick Start
3. copy and paste gimbal.py to your main package
4. Go to the Robot Dashboard Site
5. Create a Joystick that publishes to the topic /transform
