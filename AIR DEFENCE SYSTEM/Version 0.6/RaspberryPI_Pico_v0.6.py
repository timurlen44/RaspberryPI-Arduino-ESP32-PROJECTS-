from machine import Pin, PWM
from sys import stdin
import time
import sys
import select

led = Pin(25, Pin.OUT)
led.value(0)

pwm = PWM(Pin(2))
pwm.freq(50)
pwm.duty_ns(500000)

def _map(x, in_min, in_max, out_min, out_max):
    return (int((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min))*10000

while True:    
    time.sleep(0.1)    
    while sys.stdin in select.select([sys.stdin], [], [], 0)[0]:
        angle_str = ''
        while(True):
            ch = sys.stdin.read(1)
            if(ch == '\n'):
                break
            else:
                angle_str += ch
               
        angle = _map(int(angle_str), 0, 180, 40, 260)
        pwm.duty_ns(angle)
        led.toggle()