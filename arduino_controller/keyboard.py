from pynput.keyboard import Key, Listener
import serial 

ser = serial.Serial("COM4", baudrate=100000)

while True:
    ser.write(1)
    print("Wrote value", end="\n")
