import serial
import time
import cv2
import numpy as np
#import _thread

Lazer_X = 136
Lazer_Y = 141

Xposition = 90
Yposition = 50
pos_step = 3
sensivity = 60

g = (0,255,0) # green
r = (0,0,255) # red
t = 3 # thickness

lower_red = np.array([78,54,178])
upper_red = np.array([179,209,241])

blue_lower = np.array([103,135,36], np.uint8)
blue_upper = np.array([160,255,255], np.uint8)

kernel = np.ones((5,5), np.uint8)
"""
def thread_func():
    global Lazer_X
    global Lazer_Y
    global lower_red
    global upper_red
    global hsv
    global kernel
    global frame
    while True:
        mask = cv2.inRange(hsv,lower_red,upper_red)
        mask = cv2.dilate(mask, kernel, iterations=10) 
        contours, hierarchy = cv2.findContours(mask, cv2.RETR_TREE,cv2.CHAIN_APPROX_NONE)
        for contour in contours:
            area = cv2.contourArea(contour)    
            if area > 1:
                M = cv2.moments(contour)
                Lazer_X = int(M['m10']/M['m00'])
                Lazer_Y = int(M['m01']/M['m00'])
                
                print("Lazer Kordinatlari: ",str(Lazer_X),"-",str(Lazer_Y))
"""



cap = cv2.VideoCapture(0)
ser = serial.Serial("/dev/ttyUSB0", '9600', timeout=2)



def yatay_ser(y):
    gonder =  str(y+200) + 'a'
    ser.write(gonder.encode('utf-8'))
    time.sleep(0.01)
    
def dikey_ser(d):
    gonder = str(d) + 'a'
    ser.write(gonder.encode('utf-8'))
    time.sleep(0.01)



"""
_, frame = cap.read()
frame = cv2.flip(frame, 0)
frame = cv2.resize(frame, (300, 300))
hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
"""
"""
try:
    _thread.start_new_thread( thread_func, () )# print_time: bu thread in hangi fonksiyonu kullandığını belirtiyor ("Thread-1", 1) kısmı ise fonksiyona geçilecek argümanları gösteriyor
    
except:
    print ("Error : threadler çalışmadı")
"""
_, frame = cap.read()
rows, cols, _ = frame.shape
center_x = int(rows / 2)
center_y = int(cols / 2)


        
        





while True:
    _, frame = cap.read()
    frame = cv2.flip(frame, 0)
    frame = cv2.resize(frame, (300, 300))
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    mask2 = cv2.inRange(hsv,lower_red,upper_red)
    mask2 = cv2.dilate(mask2, kernel, iterations=10) 
    contours2, hierarchy2 = cv2.findContours(mask2, cv2.RETR_TREE,cv2.CHAIN_APPROX_NONE)
    for contour in contours2:
            area = cv2.contourArea(contour)    
            if area > 1:
                M = cv2.moments(contour)
                Lazer_X = int(M['m10']/M['m00'])
                Lazer_Y = int(M['m01']/M['m00'])
                print("Lazer Kordinatlari: ",str(Lazer_X),"-",str(Lazer_Y))
    
    mask = cv2.inRange(hsv, blue_lower, blue_upper)
    contours, _ = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    contours = sorted(contours,key=lambda x:cv2.contourArea(x),reverse=True)
    for cnt in contours:
        if cv2.contourArea(cnt) < 100:
            break
        (x, y, w, h) = cv2.boundingRect(cnt)
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
        #text = "x = "+str(x)+"y = "+str(y)
        #cv2.putText(frame, text, (x, y), cv2.FONT_HERSHEY_SIMPLEX, 0.50, (0, 0, 255))
        #////////////////////////////////////////////////////////////////////
        medium_x = int((x + x+w)/2)
        medium_y = int((y + y+h)/2)
        #////////////////////////////////////////////////////////////////////
        cv2.line(frame, (medium_x,0),(medium_x,600),(0,255,0),2)
        text2 = "mediumX = " + str(medium_x)
        cv2.putText(frame, text2, (0, 100), cv2.FONT_HERSHEY_SIMPLEX, 0.50, (0, 255, 50))
        #////////////////////////////////////////////////////////////////////
        cv2.line(frame, (0, medium_y), (600, medium_y), (0, 255, 0), 2)
        text3 = "mediumY = " + str(medium_y)
        cv2.putText(frame, text3, (0, 50), cv2.FONT_HERSHEY_SIMPLEX, 0.50, (0, 255, 50))

        # ////////////////////////////////////////////////////////////////////
        
        if medium_x > Lazer_X + sensivity:
            Xposition += pos_step
            if Xposition > 180:
                Xposition = 180
            #ser.write((str(Xposition) + 'y').encode('utf-8'))
            yatay_ser(Xposition)
            _, frame = cap.read()
            frame = cv2.flip(frame, 0)
            frame = cv2.resize(frame, (300, 300))
            hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
           
        if medium_x < Lazer_X - sensivity:
            Xposition -= pos_step
            if Xposition < 0:
                Xposition = 0
            #ser.write((str(Xposition) + 'y').encode('utf-8'))
            yatay_ser(Xposition)
            _, frame = cap.read()
            frame = cv2.flip(frame, 0)
            frame = cv2.resize(frame, (300, 300))
            hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        
        if medium_y > Lazer_Y + sensivity:
            Yposition += pos_step
            if(Yposition > 100):
                Yposition = 100
            #ser.write((str(Yposition) + 'd').encode('utf-8'))
            dikey_ser(Yposition)
            _, frame = cap.read()
            frame = cv2.flip(frame, 0)
            frame = cv2.resize(frame, (300, 300))
            hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

        if medium_y < Lazer_Y - sensivity:
            Yposition -= pos_step
            if(Yposition < 30):
                Yposition = 30
            #ser.write((str(Yposition) + 'd').encode('utf-8'))
            dikey_ser(Yposition)
            _, frame = cap.read()
            frame = cv2.flip(frame, 0)
            frame = cv2.resize(frame, (300, 300))
            hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
            
        print("Kordinatlar: ",str(medium_x),"-",str(medium_y))
        

        break


    #cv2.imshow("frame",frame)
    #cv2.imshow("mask",mask )
    key = cv2.waitKey(1)
    if key ==27:
        break
cap.release()
cv2.destroyAllWindows()









