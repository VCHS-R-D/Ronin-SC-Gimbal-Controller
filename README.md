# Project Goals

Controlling the Ronin SC Gimbal with:

- Directly from a Raspberry Pi (in progress)
- Arduino (done)
- Roboquest ROS System on a Raspberry Pi (done)

# Circuit

![B3B34C7C-5882-4E6B-92DE-43166F233875](https://user-images.githubusercontent.com/72239682/203432870-04043f85-1c44-4fe1-934b-ee7d6ade57bf.jpeg)
- Inverter is for inverting the serial signal from TX into an SBUS signal
- Raspberry pi connects to arduino board through uart channel and software serial
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
