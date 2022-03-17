#include<Servo.h>
Servo horizontal_ser ;
Servo vertical_ser ;
Servo trigger_ser ;
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
        i++;
        break;
      }
    }

    angle = "";
    for(;i<len;i++){
      angle += str[i];
    }
    trigger_ser.write(angle.toInt());
    
  }

}
