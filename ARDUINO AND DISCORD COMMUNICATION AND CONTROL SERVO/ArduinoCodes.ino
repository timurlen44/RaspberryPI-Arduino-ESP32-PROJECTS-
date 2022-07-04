#include <Servo.h>
#define SERVO_PIN 6
Servo servo;
String ReceivedData;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
  servo.write(60);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    ReceivedData = Serial.readStringUntil('\n');
    servo.write(ReceivedData.toInt());
  }

  delay(50);
}
