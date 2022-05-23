"""
    GUI TO CONTROL THE LEDS WITH SERIAL COMMUNICATION WITH ARDUINO
"""

#ip_and_port=('169.254.133.100',80)

import socket
import tkinter as tk
import serial
import _thread
import time
ServerIP = '127.0.0.1'


def UDP_SERVER():
    UDPServer = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
    UDPServer.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    UDPServer.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    UDPServer.bind(("", 54000))
    global ServerIP
    print("UDP Server begin.")
    while True:
        while True:
            data, addr = UDPServer.recvfrom(1024)
            print("gelen data = ",str(data))
            if(data == b'SERVER'):
                ServerIPLabel['text'] = addr[0]
                ServerIP = addr[0]
                print('IP: {}'.format(addr[0]))



def send_to_arduino(data):
    print("data: {}".format(data))
    TCPClient = socket.socket(socket.AF_INET, socket.SOCK_STREAM)#Create  socket AF_INET == IPv4 , SOCK_STREAM == TCP
    #TCPClient.settimeout(1)
    print("ServerIP: {}".format(ServerIP))
    TCPClient.connect((ServerIP,54000))#Connect server
    TCPClient.send(data.encode('utf-8'))#send data to server
    TCPClient.close()#close socket

form = tk.Tk()
form.title("PATRIOT GUI")
size = 300
size2 = 225
Buton_width  = 150
Buton_height = 75

form.geometry('300x225')
form.maxsize(size,size2)
form.minsize(size,size2)

def OPEN_FIRE_FUNC():
    send_to_arduino("ADS")
    
def STOP_FIRE_FUNC():
    send_to_arduino("DDS")
    
def OPEN_AUTO_FIRE_FUNC():
    send_to_arduino("OAF")
    
def STOP_AUTO_FIRE_FUNC():
    send_to_arduino("SAF")
    
    


OPEN_FIRE=tk.Button(text='ACTIVE DEFENSE SYSTEM',fg='black',bg='red',command=OPEN_FIRE_FUNC)
OPEN_FIRE.place(x=0,y=0)
OPEN_FIRE.place(width=Buton_width,height=Buton_height)
STOP_FIRE=tk.Button(text='DEACTIVE DEFENSE SYSTEM',fg='black',bg='red',command=STOP_FIRE_FUNC)
STOP_FIRE.place(x=150,y=0)
STOP_FIRE.place(width=Buton_width,height=Buton_height)

OPEN_AUTO_FIRE=tk.Button(text='OPEN AUTO FIRE',fg='black',bg='red',command=OPEN_AUTO_FIRE_FUNC)
OPEN_AUTO_FIRE.place(x=0,y=75)
OPEN_AUTO_FIRE.place(width=Buton_width,height=Buton_height)
STOP_AUTO_FIRE=tk.Button(text='STOP AUTO FIRE',fg='black',bg='red',command=STOP_AUTO_FIRE_FUNC)
STOP_AUTO_FIRE.place(x=150,y=75)
STOP_AUTO_FIRE.place(width=Buton_width,height=Buton_height)

ServerIPLabel = tk.Label(form,text='IP ADDRESS DONT KNOWN')
ServerIPLabel.place(x = 0,y = 150)
ServerIPLabel.place(width=Buton_width,height=Buton_height)
ServerPORT = tk.Label(form,text = 'PORT: 54000')
ServerPORT.place(x = 150,y = 150)
ServerPORT.place(width=Buton_width,height=Buton_height)

try:
    _thread.start_new_thread( UDP_SERVER, () )
    
except:
    print ("Error : Thread Do Not Work")
print("Server: {}".format(ServerIP))
form.mainloop()
