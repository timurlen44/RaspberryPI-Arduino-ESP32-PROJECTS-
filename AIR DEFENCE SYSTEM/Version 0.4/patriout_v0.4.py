import serial
import time
import cv2
import numpy as np
import _thread
import os.path

Lazer_X = 150
Lazer_Y = 150

Xposition = 90
Yposition = 50
pos_step = 1
sensivity = 40

control1=0
control2=0
control3=0
control4=0

blue_lower = np.array([75,201,49], np.uint8)
blue_upper = np.array([129,255,255], np.uint8)



kernel = np.ones((5,5), np.uint8)

file_path = ''


cap = cv2.VideoCapture(0)
def check_file(_file_path):
    global file_path
    if os.path.exists(_file_path):
        file_path = _file_path




check_file("/dev/ttyUSB0")
check_file("/dev/ttyUSB1")

while file_path == '':
    print('please connect arduino')
    check_file("/dev/ttyUSB0")
    check_file("/dev/ttyUSB1")
    time.sleep(3)

ser = serial.Serial(file_path, '1000000', timeout=2)


    



trig_pos = 0
def thread_func():
    global trig_pos
    _trig = 0
    counter = time.perf_counter()
    counter2 = time.perf_counter()
    gonder =''
    trig_str=''
    reload_time = 0.25
    global wait
    while True:
        gonder = str(Xposition)+'a' + str(Yposition) + 'b'
        
        
        counter2 = time.perf_counter()
        if(trig_pos == 1 and _trig == 0):
            counter = time.perf_counter()
            _trig = 1
            trig_str= '60x'

        elif(_trig == 1 and (counter2 - counter) > reload_time):
            trig_str= '0x'
            _trig = 0
        elif(_trig != 1 and trig_pos == 0):
            trig_str= '0x'
            _trig = 0
        gonder += trig_str
        print("gpnder: ",gonder)
        ser.write(gonder.encode('utf-8'))
        time.sleep(0.15)
        
try:
    _thread.start_new_thread( thread_func, () )
    
except:
    print ("Error : Thread Do Not Work")


_, frame = cap.read()
rows, cols, _ = frame.shape
center_x = int(rows / 2)
center_y = int(cols / 2)


while True:
    _, frame = cap.read()
    frame = cv2.flip(frame, 0)
    frame = cv2.resize(frame, (300, 300))
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    mask = cv2.inRange(hsv, blue_lower, blue_upper)
    contours, _ = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    if not contours:
        trig_pos = 0
    
    contours = sorted(contours,key=lambda x:cv2.contourArea(x),reverse=True)
    for cnt in contours:
        if cv2.contourArea(cnt) < 10:
            trig_pos = 0
            break
        #////////////////////////////////////////////////////////////////////        
        (x, y, w, h) = cv2.boundingRect(cnt)
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
        medium_x = int((x + x+w)/2)
        medium_y = int((y + y+h)/2)
        # ////////////////////////////////////////////////////////////////////
        control1=0
        control2=0
        control3=0
        control4=0
        if medium_x > Lazer_X + sensivity:
            Xposition += pos_step
            if Xposition > 180:
                Xposition = 180

        else:
            control1 = 1
           
        if medium_x < Lazer_X - sensivity:
            Xposition -= pos_step
            if Xposition < 0:
                Xposition = 0
        else:
            control2 = 1
        if medium_y > Lazer_Y + sensivity:
            Yposition += pos_step
            if(Yposition > 100):
                Yposition = 100
            
        else:
            control3 = 1
        if medium_y < Lazer_Y - sensivity:
            Yposition -= pos_step
            if(Yposition < 30):
                Yposition = 30
        else:
            control4 = 1
            
        if(control1 and control2 and control3 and control4):
            trig_pos = 1
        else:
            trig_pos = 0
        
        #print("Coordinates: ",str(medium_x),"-",str(medium_y))
        

        break


    cv2.imshow("frame",frame)
    cv2.imshow("mask",mask )
    key = cv2.waitKey(1)
    if key ==27:
        break
cap.release()
cv2.destroyAllWindows()










