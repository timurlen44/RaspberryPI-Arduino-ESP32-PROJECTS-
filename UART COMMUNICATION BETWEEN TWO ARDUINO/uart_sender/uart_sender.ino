#define LED1 A2
#define LED2 A3
#define LED3 A4
#define LED4 A5
void setup() {
  Serial.begin(9600);
  init_button_pins();
}
void loop() {
  if (digitalRead(LED1)){
    Serial.write("1", 1);
    while(digitalRead(LED1));
    Serial.write("0",1);
  }
  if (digitalRead(LED2)){
    Serial.write("2", 1);
    while(digitalRead(LED2));
    Serial.write("0",1);
  }
  if (digitalRead(LED3)){
    Serial.write("3", 1);
    while(digitalRead(LED3));
    Serial.write("0",1);
  }
  if (digitalRead(LED4)){
    Serial.write("4", 1);
    while(digitalRead(LED4));
    Serial.write("0",1);
  }
}

void init_button_pins(){
  pinMode(INPUT,LED1);
  pinMode(INPUT,LED2);
  pinMode(INPUT,LED3);
  pinMode(INPUT,LED4);
}
