#define RED   6
#define GREEN 7
#define SERVO_PIN 9
#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h>
Servo servo;
String condition1 = "TURN ON RED LED";
String condition2 = "TURN OFF RED LED";
String condition3 = "TURN ON GREEN LED";
String condition4 = "TURN OFF GREEN LED";
String ReceivedData = "";

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
bool veri_al = false;
IPAddress ip(169,254,69,60);
EthernetServer server(80);

void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  Ethernet.init(10);  // Most Arduino shields
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  servo.attach(9);
  servo.write(0);


  if (Ethernet.begin(mac, 1000, 1000) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  // Open serial communications and wait for port to open:


  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");

    while (client.connected() || client.available()) { //connected or data available

      char c = client.read(); //gets byte from ethernet buffer

      if (c == '#' && veri_al == 0) {
        veri_al = 1;
      }
      else if (c == '#' && veri_al == 1) {
        veri_al = 0;

        control_conditions();
        Serial.println("ReceivedData: " + ReceivedData);
        ReceivedData = "";
      }
      else if (veri_al == 1 && c != '#') {
        ReceivedData += c;
      }


    }

    delay(1);
    client.stop();
    Serial.println("client disconnected");
  }
}


void ArduinoTCPServer() {

}

void control_conditions() {
  if (condition1.equals(ReceivedData)) {
    digitalWrite(RED, HIGH);
    Serial.println("kirmizi yandi");
  }
  else if (condition2.equals(ReceivedData)) {
    digitalWrite(RED, LOW);
    Serial.println("kirmizi sondu");
  }

  else if (condition3.equals(ReceivedData)) {
    digitalWrite(GREEN, HIGH);
    Serial.println("yesil yandi");
  }
  else if (condition4.equals(ReceivedData)) {
    digitalWrite(GREEN, LOW);
    Serial.println("yesil sondu");
  }
  else {
    Serial.println("servo geldi");
    servo.write(ReceivedData.toInt());
  }

}
