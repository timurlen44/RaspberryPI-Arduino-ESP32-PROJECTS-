import time
import telepot
import RPi.GPIO as GPIO
import cv2
import _thread

LED1 = 17
LED2 = 27
LED3 = 23
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(LED1, GPIO.OUT)
GPIO.setup(LED2, GPIO.OUT)
GPIO.setup(LED3, GPIO.OUT)
vid = cv2.VideoCapture(0)

camera_window_is_open = False
open_camera_command = False
receiveTelegramMessage = False
sendTelegramMessage = False

statusText = ""
led1Status = False
led2Status = False
led3Status = False

def thread_func():
  global camera_window_is_open
  global open_camera_command
  global receiveTelegramMessage
  global sendTelegramMessage
  
  global led1Status
  global led2Status
  global led3Status
  while True:
    if receiveTelegramMessage == True:
      receiveTelegramMessage = False
      statusText = ""
            
      if telegramText == "LED1 ON":
        print("Turn on LED1")
        GPIO.output(LED1, GPIO.HIGH)
        led1Status = True
      elif telegramText == "LED1 OFF":
        GPIO.output(LED1, GPIO.LOW)
        print("Turn off LED1")
        led1Status = False
      elif telegramText == "LED2 ON":
        GPIO.output(LED2, GPIO.HIGH)
        print("Turn on LED2")
        led2Status = True
      elif telegramText == "LED2 OFF":
        print("Turn off LED2")
        GPIO.output(LED2, GPIO.LOW)
        led2Status = False
      elif telegramText == "LED3 ON":
        GPIO.output(LED3, GPIO.HIGH)
        print("Turn on LED3")
        led3Status = True
      elif telegramText == "LED3 OFF":
        print("Turn off LED3")
        GPIO.output(LED3, GPIO.LOW)
        led3Status = False
      elif telegramText == "CAMERA ON":
        open_camera_command = True
      elif telegramText == "CAMERA OFF":
        open_camera_command = False
      else:
        statusText = "Command not valid\n\n"
      
      statusText = statusText + "Status:\n"
      if led1Status == True:
        statusText = statusText + "LED1 ON\n"
      elif led1Status == False:
        statusText = statusText + "LED1 OFF\n"
      if led2Status == True:
        statusText = statusText + "LED2 ON\n"
      elif led2Status == False:
        statusText = statusText + "LED2 OFF\n"
      if led3Status == True:
        statusText = statusText + "LED3 ON\n"
      elif led3Status == False:
        statusText = statusText + "LED3 OFF\n"
      if open_camera_command == True:
        statusText = statusText + "CAMERA ON\n"
      else:
        statusText = statusText + "CAMERA OFF\n"
      
            
      sendTelegramMessage = True
      if sendTelegramMessage == True:
          sendTelegramMessage = False
          bot.sendMessage(chat_id, statusText)

def reset_pins():
  GPIO.output(LED1, GPIO.LOW)
  GPIO.output(LED2, GPIO.LOW)
  GPIO.output(LED3, GPIO.LOW)
def handle(msg):
  global telegramText
  global chat_id
  global receiveTelegramMessage
  
  chat_id = msg['chat']['id']
  telegramText = msg['text']
  
  #print("CHAT ID: " + str(chat_id))
  
  if telegramText == "/start":
    bot.sendMessage(chat_id, "RELAY CONTROL")
  
  else:
    receiveTelegramMessage = True

_thread.start_new_thread( thread_func, () )
bot = telepot.Bot('Write Yor Telegram Bot Token')
bot.message_loop(handle)

print("BOT IS READY")



reset_pins()
try:
    while True:
      
      if(open_camera_command == True):
        camera_window_is_open = True
        ret, frame = vid.read()
        frame = cv2.flip(frame, 0)
        cv2.imshow('frame', frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
          break
      elif(camera_window_is_open == True):
        camera_window_is_open = False
        cv2.destroyAllWindows()
      """
        if receiveTelegramMessage == True:
            receiveTelegramMessage = False

            statusText = ""
            
            if telegramText == "LED1 ON":
                print("Turn on LED1")
                GPIO.output(LED1, GPIO.HIGH)
                led1Status = True
            elif telegramText == "LED1 OFF":
                GPIO.output(LED1, GPIO.LOW)
                print("Turn off LED1")
                led1Status = False
            elif telegramText == "LED2 ON":
                GPIO.output(LED2, GPIO.HIGH)
                print("Turn on LED2")
                led2Status = True
            elif telegramText == "LED2 OFF":
                print("Turn off LED2")
                GPIO.output(LED2, GPIO.LOW)
                led2Status = False
                led2.off()
            elif telegramText == "LED3 ON":
                GPIO.output(LED3, GPIO.HIGH)
                print("Turn on LED3")
                led3Status = True
            elif telegramText == "LED3 OFF":
                print("Turn off LED3")
                GPIO.output(LED3, GPIO.LOW)
                led3Status = False

            else:
                statusText = "Command not valid\n\n"

            statusText = statusText + "Status:\n"
            if led1Status == True:
                statusText = statusText + "LED1 ON\n"
            elif led1Status == False:
                statusText = statusText + "LED1 OFF\n"
            if led2Status == True:
                statusText = statusText + "LED2 ON\n"
            elif led2Status == False:
                statusText = statusText + "LED2 OFF\n"
            if led3Status == True:
                statusText = statusText + "LED3 ON\n"
            elif led3Status == False:
                statusText = statusText + "LED3 OFF\n"
            
            sendTelegramMessage = True

        if sendTelegramMessage == True:
            sendTelegramMessage = False
            bot.sendMessage(chat_id, statusText)
         """
      

except KeyboardInterrupt:
    reset_pins()
    vid.release()
    cv2.destroyAllWindows()
    sys.exit(0)

