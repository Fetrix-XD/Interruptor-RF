#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include "PCF8574.h"
// MAPA DE CONEXIONES
//D0----->RST LoRa
//D1----->SCL I2C
//D2----->SDA I2C
//D3----->none
//D4----->DIO0 LoRa
//D5----->SCK  LoRa
//D6----->MISO LoRa
//D7----->MOSI LoRa
//D8----->NSS  LoRa
//I2C
//P0----->-switck1---->Gnd esp
//P1----->-switck2---->Gnd esp
//P2----->-switck3---->Gnd esp
//P3----->-Switck4---->Gnd esp
//P4----->Led1
//P5----->Led2
//P6----->Led3
//P7----->Led4


#define ss 15   //D8
#define rst 16  //D0
#define dio0 0  //D4
int counter = 0;
PCF8574 expan(0x24);

int luz1;
int luz2;
int luz3;
int luz4;

void setup()
{
  Serial.begin(9600);
  expan.pinMode(P0, INPUT);
  expan.pinMode(P1, INPUT);
  expan.pinMode(P2, INPUT);
  expan.pinMode(P3, INPUT);
  expan.pinMode(P4, OUTPUT);
  expan.pinMode(P5, OUTPUT);
  expan.pinMode(P6, OUTPUT);
  expan.pinMode(P7, OUTPUT);
  if (expan.begin()) {
    Serial.println("OK");
  } else {
    Serial.println("Error");
  }

  while (!Serial);
  Serial.println("LoRa Sender");
  LoRa.setPins(ss, rst, dio0);
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    delay(100);
    while (1);
  }
}

void loop() {
  if (expan.digitalRead(P0) == HIGH) {
    luz1 = 0;
  }
  else {
    luz1 = 1;
  }
  if (expan.digitalRead(P1) == HIGH) {
    luz2 = 0;
  }
  else {
    luz2 = 1;
  }

  if (luz1 == 1) {
    LoRa.beginPacket();
    Serial.print("paquete:");
    Serial.println(counter);
    LoRa.print("ON1 1234");
    Serial.println("Pin: on1");
  } else {
    LoRa.beginPacket();
    Serial.print("paquete:");
    Serial.println(counter);
    LoRa.print("OFF1 1234");
    Serial.println("Pin: OFF1");
  }
  LoRa.endPacket();
  counter++;
  delay(1000);

  if (luz2 == 1) {
    LoRa.beginPacket();
    Serial.print("paquete:");
    Serial.println(counter);
    LoRa.print("ON2 1234");
    Serial.println("Pin: on2");
  } else {
    LoRa.beginPacket();
    Serial.print("paquete:");
    Serial.println(counter);
    LoRa.print("OFF2 1234");
    Serial.println("Pin: OFF2");
  }

  LoRa.endPacket();
  counter++;
  delay(1000);
}
