#include <SPI.h>
#include <LoRa.h>
#include "PCF8574.h"

//#define led1 5
//#define led2 16
#define ss 15
#define rst 16
#define dio0 0

PCF8574 expan(0x24);

void setup() {
  Serial.begin(9600);
  expan.pinMode(P0,OUTPUT);
  expan.pinMode(P1,OUTPUT);
  expan.pinMode(P2,OUTPUT);
  expan.pinMode(P3,OUTPUT);
  if(expan.begin()){
    Serial.println("OK");
  }else{
    Serial.println("Error");
  }
  
  while (!Serial);
  Serial.println("LoRa Receiver Callback");
  LoRa.setPins(ss, rst, dio0);
  expan.digitalWrite(P0, HIGH);
  expan.digitalWrite(P1, HIGH);
 
  if (!LoRa.begin(433E6)){
    Serial.println("Starting LoRa failed!");
    while (1);
  }
 
  // register the receive callback
  LoRa.onReceive(onReceive);
 
  // put the radio into receive mode
  LoRa.receive();
  
}
 
void loop() {
  // do nothing
}
 
void onReceive(int packetSize){
  // received a packet
  String message = "";
  Serial.print("Received packet: ");
  while(LoRa.available()){
    message += (char)LoRa.read();
  }
  Serial.println(message);

  // extract the key from the message
  int lastSpacePos = message.lastIndexOf(" ");
  String key = message.substring(lastSpacePos + 1);
  if (key == "1234") { // compare the key with the known key
    if (message.startsWith("ON1")) {
      expan.digitalWrite(P0, LOW);
      Serial.println("Encendido");
    }else if (message.startsWith("OFF1")) {
      expan.digitalWrite(P0, HIGH);
      Serial.println("Apagado");}
    else {
      Serial.println("Error: Mensaje desconocido 1");
    }  
    if(message.startsWith("ON2")) {
      expan.digitalWrite(P1, LOW);
      Serial.println("Encendido2");
    }
    else if (message.startsWith("OFF2")) {
      expan.digitalWrite(P1, HIGH);
      Serial.println("Apagado2");}
    else {
      Serial.println("Error: Mensaje desconocido 2");
    }
  }
  else {
    Serial.println("Error: Clave de verificación incorrecta");
  }
}
