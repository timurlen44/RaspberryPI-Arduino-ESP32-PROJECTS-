#include<Servo.h>
Servo horizontal_ser ;
Servo vertical_ser ;
Servo trigger_ser ;
char x;
long int v;
String str = "";
String angle="";
int i = 0;
int len = 0;
void setup() {
  horizontal_ser.attach(11);
  horizontal_ser.write(90);
  vertical_ser.attach(10);
  vertical_ser.write(50);
  trigger_ser.attach(6);
  trigger_ser.write(0);
  Serial.begin(1000000);


}

void loop() {
  if (Serial.available() > 2) {
    str = Serial.readStringUntil('x');
    len = str.length();

    angle = "";
    for(i = 0;i<len;i++){
      angle += str[i];
      if(str[i] == 'a'){
        //Serial.println(String("angle1: ")+String(angle.toInt()));
        horizontal_ser.write(angle.toInt());
        i++;
        break;
      }
    }

    angle = "";
    for(;i<len;i++){
      angle += str[i];
      if(str[i] == 'b'){
        vertical_ser.write(angle.toInt());
        //Serial.println(String("angle2 ")+String(angle.toInt()));
        i++;
        break;
      }
    }

    angle = "";
    for(;i<len;i++){
      angle += str[i];
    }
  //Serial.println(String("angle3: ")+String(angle.toInt()));
    trigger_ser.write(angle.toInt());
    
  }

}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             















/*
  #include<Servo.h>
  Servo yat_ser ;
  Servo dik_ser ;
  String ReceivedData = "";
  int length = 0;
  int angle = 0;
  long int v;
  void setup() {
  yat_ser.attach(11);
  yat_ser.write(90);
  dik_ser.attach(10);
  dik_ser.write(50);
  tetik_ser.attach(6);
  tetik_ser.write(0);
  Serial.begin(9600);

  }

  void loop() {
  if (Serial.available() > 2) {
    ReceivedData = Serial.readStringUntil('\n');
    length = ReceivedData.length() - 1;
    angle = ReceivedData.toInt();
    if (ReceivedData[length] == 'y') {
      yat_ser.write(angle);
    }
    else if (ReceivedData[length] == 'd') {
      dik_ser.write(angle);
    }
    else if (ReceivedData[length] == 't') {
      if (angle == 180) {
        digitalWrite(6, HIGH);
      }
      else if (angle == 0) {
        digitalWrite(6, LOW);
      }
    }

    delay(10);
  }

  }
*/
