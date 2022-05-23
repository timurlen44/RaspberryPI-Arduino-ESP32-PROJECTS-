#include <Servo.h>
#define SERVO_PIN 6
#define SERVO_CONTROL_PIN A0
#define TETIK_GERI 70
#define TETIK_ILERI 5
Servo servo;
String ReceivedData;
void setup() {
  // put your setup code here, to run once:
  pinMode(SERVO_CONTROL_PIN,INPUT);
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
  servo.write(TETIK_GERI);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(SERVO_CONTROL_PIN) == 1) {
    servo.write(TETIK_ILERI);
  }
  else{
    servo.write(TETIK_GERI);
  }

  delay(50);
}
