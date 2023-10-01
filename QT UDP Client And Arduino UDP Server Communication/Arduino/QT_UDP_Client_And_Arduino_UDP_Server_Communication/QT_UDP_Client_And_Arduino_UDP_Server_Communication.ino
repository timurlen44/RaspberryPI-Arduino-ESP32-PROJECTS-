#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define UDP_RX_PACKET_MAX_SIZE 33

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
void initLcd();
void printLcd(String firstLine, String secondLine);
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(169, 254, 69, 60);

unsigned int localPort = 54000;      // local port to listen on

// buffers for receiving and sending data
char packetBuffer[UDP_RX_PACKET_MAX_SIZE] = {0};  // buffer to hold incoming packet,
//char ReplyBuffer[] = "HELLO CLIENT";        // a string to send back

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP UDP;

void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  initLcd();
  
  
  Ethernet.init(10);  // Most Arduino shields

  // start the Ethernet
  Ethernet.begin(mac, ip);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("max karakter: ");
  Serial.println(UDP_RX_PACKET_MAX_SIZE);
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

  // start UDP
  UDP.begin(localPort);
  Serial.println("UDP BASLADI");
}

void loop() {
  // if there's data available, read a packet
  int packetSize = UDP.parsePacket();
  if (packetSize) {

    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");

    Serial.print("CLIENT IP: ");
    IPAddress remote = UDP.remoteIP();
    for (int i = 0; i < 4; i++) {
      Serial.print(remote[i], DEC);
      if (i < 3) {
        Serial.print(".");
      }
    }
    Serial.print("\nCLIENT PORT: ");
    Serial.println(UDP.remotePort());

    // read the packet into packetBufffer
    memset(packetBuffer, '\0', UDP_RX_PACKET_MAX_SIZE);
    UDP.read(packetBuffer, UDP_RX_PACKET_MAX_SIZE);

    Serial.print("packetBuffer: ");
    Serial.println(packetBuffer);


    
    String packetBuffer_str = packetBuffer;
    //strcpy(packetBuffer_str, packetBuffer);
    Serial.print("Gelen messaj: ");
    Serial.println(packetBuffer_str);
    String firstLine;
    String secondLine;

    // İlk 16 karakteri firstLine'a kopyala
    firstLine = packetBuffer_str.substring(0, 16);
    Serial.print("firstLine: ");
    Serial.println(firstLine);

    // Sonraki 16 karakteri secondLine'a kopyala
    secondLine = packetBuffer_str.substring(16, 32);
    
    Serial.print("secondLine: ");
    Serial.println(secondLine);
    
    printLcd(firstLine, secondLine);
    Serial.print("MESSAGE FROM CLIENT: ");
    Serial.println(packetBuffer);

    // send a reply to the IP address and port that sent us the packet we received
    //UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
    //UDP.write(ReplyBuffer);
    //UDP.endPacket();
  }
  delay(10);
}


void printLcd(String firstLine, String secondLine)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(firstLine);
  lcd.setCursor(0, 1);
  lcd.print(secondLine);
}
void initLcd()
{
  lcd.init();
  lcd.backlight();
  lcd.clear();
  printLcd("WAITING MESSAGE!", "WAITING MESSAGE!");
}
