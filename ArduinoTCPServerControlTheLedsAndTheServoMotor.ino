#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h>
Servo servo;
String condition1 = "TURN ON LED1";
String condition2 = "TURN OFF LED1";
String condition3 = "TURN ON LED2";
String condition4 = "TURN OFF LED2";
String ReceivedData = "";
#define LED1 A4
#define LED2 A5
#define SERVO_PIN 9

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
bool veri_al = false;
IPAddress ip(169, 254, 133, 100);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  Ethernet.init(10);  // Most Arduino shields
  Serial.begin(9600);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
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
        Serial.println("ReceivedData: "+ReceivedData);
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
  else {
    servo.write(ReceivedData.toInt());
  }

}
