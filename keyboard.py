from pynput import keyboard
from serial import Serial
import time

ser = Serial("/dev/ttyAMA0", baudrate=9600)

def on_press(key):
    try:
        print(f'key {key.char} pressed ')
        
        if key.char == '1':
            ser.write(b'1')
        if key.char == '2':
            ser.write(b'2')
    except AttributeError:
        print('special key {0} pressed'.format(
            key))

def on_release(key):
    print('{0} released'.format(
        key))
    if key == keyboard.Key.esc: # escape
        # Stop listener
        return False

# ...or, in a non-blocking fashion:
with keyboard.Listener(
        on_press=on_press,
        on_release=on_release) as listener:
    listener.join()

