#include<Servo.h>
Servo yat_ser ;
Servo dik_ser ;
char x;
long int v;
void setup() {
yat_ser.attach(11);
yat_ser.write(90);
dik_ser.attach(10);
dik_ser.write(50);
 Serial.begin(9600);
   
   
}

void loop() {
if(Serial.available()>2){
  x =Serial.read();
  v =Serial.parseInt();
  if(x =='a'){
    if(v > 199){
    yat_ser.write(v-200);  
    }
    else{
      dik_ser.write(v);    
    }
    
  }
  /*
  if(x == 'd'){
    dik_ser.write(v);  
  }
  */
  delay(10);
  }
  
}
