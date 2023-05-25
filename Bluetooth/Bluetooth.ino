//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial
#include <iostream>
#include <string>
using namespace std;
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#include "FastLED.h"
#define NUM_LEDS 50

#include <thread>
#define DATA_PIN 4 
String message = "";
int red;
int green;
int blue;
CRGB leds[NUM_LEDS];
BluetoothSerial SerialBT;

void color_mode(String color){
      red=color.substring(5,8).toInt();
      blue=color.substring(9,12).toInt();
      green=color.substring(12,15).toInt();
      for (int led_index=0;led_index<50;led_index++){
      leds[led_index] = CRGB(red,blue,green);
      
      //delay(500);
    }
    FastLED.show();
  }
void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
if (SerialBT.available()){
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n'){
      message += String(incomingChar);
    }
    else{
      message = "";
    }
    Serial.write(incomingChar);  
  }
  if (message.substring(0,3)=="rgb"){
    color_mode(message);
    }
}
