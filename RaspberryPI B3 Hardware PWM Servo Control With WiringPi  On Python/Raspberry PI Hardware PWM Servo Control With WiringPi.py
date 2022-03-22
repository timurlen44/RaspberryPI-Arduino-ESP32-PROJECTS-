import time
import wiringpi
wiringpi.wiringPiSetupGpio()
pin = 12
wiringpi.pinMode(pin, wiringpi.GPIO.PWM_OUTPUT)
wiringpi.pwmSetMode(wiringpi.GPIO.PWM_MODE_MS)
wiringpi.pwmSetClock(192)
wiringpi.pwmSetRange(2000)

print("Python WiringPi Library Servo Control On Raspberry PI B3")
print("DO NOT FORGET RUN CODE WITH SUDO")

while True:
        pulse = input("Enter pulse between 40 and 260: ")
        wiringpi.pwmWrite(pin, int(pulse))
