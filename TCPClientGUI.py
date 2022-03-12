"""
    GUI TO CONTROL THE LEDS WITH SERIAL COMMUNICATION WITH ARDUINO
"""


ip_and_port=('169.254.133.100',80)

import socket
import tkinter as tk
import serial


def send_to_arduino(data):
    data2='#'+data+'#'
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)#Create  socket AF_INET == IPv4 , SOCK_STREAM == TCP
    client.connect(ip_and_port)#Connect server
    client.send(data2.encode('utf-8'))#send data to server
    client.close()#close socket

form = tk.Tk()
form.title("TCP COMMUNICATION")
size = 300
size2 = 225
Buton_width  = 150
Buton_height = 75

form.geometry('300x225')
form.maxsize(size,size2)
form.minsize(size,size2)

def LED1_TURN_ON():
    send_to_arduino("TURN ON LED1")
    
def LED1_TURN_OFF():
    send_to_arduino("TURN OFF LED1")
    
def LED2_TURN_ON():
    send_to_arduino("TURN ON LED2")
    
def LED2_TURN_OFF():
    send_to_arduino("TURN OFF LED2")
    
def SERVO_WRITE():
    send_to_arduino(_input.get())
    


LED1_ON=tk.Button(text='LED1 TURN ON',fg='black',bg='red',command=LED1_TURN_ON)
LED1_ON.place(x=0,y=0)
LED1_ON.place(width=Buton_width,height=Buton_height)
LED1_OFF=tk.Button(text='LED1 TURN OFF',fg='black',bg='red',command=LED1_TURN_OFF)
LED1_OFF.place(x=150,y=0)
LED1_OFF.place(width=Buton_width,height=Buton_height)

LED2_ON=tk.Button(text='LED2 TURN ON',fg='black',bg='red',command=LED2_TURN_ON)
LED2_ON.place(x=0,y=75)
LED2_ON.place(width=Buton_width,height=Buton_height)
LED2_OFF=tk.Button(text='LED2 TURN OFF',fg='black',bg='red',command=LED2_TURN_OFF)
LED2_OFF.place(x=150,y=75)
LED2_OFF.place(width=Buton_width,height=Buton_height)

_input=tk.Entry()
_input.place(x=0,y=150)
_input.place(width=Buton_width,height=Buton_height)
SET_ANGLE=tk.Button(text='Set Angle',fg='black',bg='red',command=SERVO_WRITE)
SET_ANGLE.place(x=150,y=150)
SET_ANGLE.place(width=Buton_width,height=Buton_height)

form.mainloop()


