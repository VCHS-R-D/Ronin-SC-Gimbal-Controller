#!/usr/bin/env python3
import rospy
from std_msgs.msg import Int32
from serial import Serial

ser = Serial("/dev/ttyAMA1", baudrate=9600)

SPEED_STOP :int = 1023
SPEED_FW :int = 500
SPEED_BW :int = 1647

"""
define STOP 1023 
define FW 500
define BW 1647
"""


def map_speed(data: int) -> int:
    return 2047 - (data - 0)*(SPEED_BW - SPEED_FW)

def callbackPan(msg):
	data = msg.data
	if (data<0):
		ser.write(b'1')
	elif (data>0):
		ser.write(b'2')
	else:
		ser.write(b'0')

def callbackTilt(msg):
	data = msg.data
	if (data<0):
		ser.write(b'3')
	elif (data>0):
		ser.write(b'4')
	else:
		ser.write(b'0')

def callbackRoll(msg):
	data = msg.data
	if (data<0):
		ser.write(b'5')
	elif (data>0):
		ser.write(b'6')
	else:
		ser.write(b'0')

def gimbal():
	rospy.init_node('gimbal',anonymous=True)
    
    #pan tilt roll subscribers
	rospy.Subscriber('pan',Int32, callbackPan)
	rospy.Subscriber('tilt',Int32, callbackTilt)
	rospy.Subscriber('roll',Int32, callbackRoll)
 	rospy.spin()
    
    ser.close()

if __name__ == '__main__':
    gimbal()
