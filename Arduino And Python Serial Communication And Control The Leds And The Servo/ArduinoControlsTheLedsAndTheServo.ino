#include <Servo.h>
String condition1 = "TURN ON LED1";
String condition2 = "TURN OFF LED1";
String condition3 = "TURN ON LED2";
String condition4 = "TURN OFF LED2";
String ReceivedData = "";
#define LED1 A4
#define LED2 A5
#define SERVO_PIN 9



Servo servo;
void control_conditions();

void setup() {
  Serial.begin(115200);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  servo.attach(9);
  servo.write(0);

}

void loop() {
  if (Serial.available()) {
    //digitalWrite(LED1,HIGH);
    ReceivedData = Serial.readStringUntil('\n');
    control_conditions();
  }

  delay(50);

}

void control_conditions() {
  if (condition1.equals(ReceivedData)) {
    digitalWrite(LED1, HIGH);
  }
  else if (condition2.equals(ReceivedData)) {
    digitalWrite(LED1, LOW);
  }

  else if (condition3.equals(ReceivedData)) {
    digitalWrite(LED2, HIGH);
  }
  else if (condition4.equals(ReceivedData)) {
    digitalWrite(LED2, LOW);
  }
  else{
    servo.write(ReceivedData.toInt());
  }

}
