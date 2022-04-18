
void setup() {
  Serial.begin(9600);
  init_pins();
  reset_pins();
}

void loop() {
  if (Serial.available() > 0) {
    char c = Serial.read();  //gets one byte from serial buffer
    if (c == '1') {
      digitalWrite(3, HIGH);
    }
    else if (c == '2') {
      digitalWrite(4, HIGH);
    }
    else if (c == '3') {
      digitalWrite(5, HIGH);
    }
    else if (c == '4') {
      digitalWrite(6, HIGH);
    }
    else if (c == '0') {
      reset_pins();
    }
  }
}
void init_pins() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

void reset_pins() {
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}
