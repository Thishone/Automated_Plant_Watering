/*
Castone Project

*/
#include <Arduino.h>
#include "blinkLed.h"
#include "analogInputOutput.h"
#include "waterPump.h"
#include "bluetooth.h"
#include <SoftwareSerial.h>

int baudRate = 9600;

void setup() 
{
  Serial.begin(baudRate);              //  setup serial
  blinkLedSetup();
  waterPumpSetup();
  bluetoothSetup();
}

// the loop function runs over and over again forever
void loop() 
{
//    blinkOnOff();

    //soil humidity
    analogReadHumidity();
    analogWriteHumidity();

    //temperature
    analogReadTemperature();
    analogWriteTemperature();

    //light
    analogReadLight();
    analogWriteLight();

    bluetooth();
    bluetoothSerial();
    
    Serial.println("\n");
}
