#include <Ethernet.h>
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

#define ds 12
#define shcp 10
#define stcp 11

byte mac[] = SECRET_MAC;

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 177);
IPAddress myDns(192, 168, 0, 1);

EthernetClient client;

unsigned long myChannelNumber =  SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

// Initialize our values
int Temperatura = 0;
int Osvetljenost = random(0,100);

double getTemp(int adc);
void shiftRegister(int data);


void setup() {
  Ethernet.init(10);  // Most Arduino Ethernet hardware
  Serial.begin(115200);  //Initialize serial
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
      
  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
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
    Ethernet.begin(mac, ip, myDns);
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak

  shiftRegister(0);
}

void loop() {
  
  // set the fields with the values
  ThingSpeak.setField(1, Temperatura); // Temperatura
  ThingSpeak.setField(2, Osvetljenost); // Osvetljenost

  
  // write to the ThingSpeak channel 
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  
  
  Osvetljenost = analogRead(A0);
  Temperatura = getTemp(analogRead(A1));
  
  delay(20000); // Wait 20 seconds to update the channel again
}

double getTemp(int adc){
  double t = (((adc * 5000.00) /1023.00) -400) /19.5;
  return t;
}

void shiftRegister(int data){
  digitalWrite(ds, LOW);
  digitalWrite(shcp, LOW);
  digitalWrite(stcp, LOW);
  for(int i=0;i<8;i++){
    digitalWrite(ds, ((data>>i) & 1));
    digitalWrite(shcp, HIGH);
    digitalWrite(shcp, LOW);
  }
  digitalWrite(stcp, HIGH);
  delay(10);
  digitalWrite(stcp, LOW);
}
