from pynput import keyboard
from serial import Serial
import time

ser = Serial("/dev/ttyAMA0", baudrate=9600)

def on_press(key):
    try:
        print("pressed:", key.char)
        ser.write(bytes(str(key.char),'utf-8'))

        #if key.char == '1':
        #    ser.write(b'1')
        #if key.char == '2':
        #    ser.write(b'2')
    except AttributeError:
        print('special key {0} pressed'.format(
            key))
def on_release(key):
    ser.write(b'0');
# ...or, in a non-blocking fashion:
with keyboard.Listener(
        on_press=on_press,
        on_release=on_release) as listener:
    listener.join()

