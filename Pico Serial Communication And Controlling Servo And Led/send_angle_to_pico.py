import serial
arduino = serial.Serial("COM11", '115200', timeout=2)

def send_to_arduino(data):
    data +='\n'
    arduino.write(data.encode('utf-8'))
    
while True:
    angle = input('Enter The Angle: ')
    send_to_arduino(angle)
    