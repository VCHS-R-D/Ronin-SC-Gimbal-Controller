# GIMBAL_PROJECT
Controling the Ronin SC directly through a raspberry pi (in progress), an arduino microcontroller (done), and the roboquest UI deployed on the raspberry pi (done)
# Setup
1. Download library from source: https://github.com/boldstelvis/BMC_SBUS
2. Extract the subdirectory "BMC_SBUS", not the whole repo, into the Arduino/libraries folder
3. Use arduino_controller.ino file in arduino_controller and upload the code to the arduino
4. Run the keyboard.py input code on a raspberry pi

# Setup for ROS
1. Flash RPI OS with roboquest software system (only available to VCHS)
2. Run the nodes in the UnitTest file
3. Open up the UI software
4. Send joystick commands through the UI joystick
