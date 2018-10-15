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
unsigned long lastSerial = 0;

#define SET_PERIOD 10
#define READ_SENSORS_PERIOD   1000*SET_PERIOD

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
  if (millis() - lastSerial >= READ_SENSORS_PERIOD)
  {
    lastSerial = millis();
    Serial.println(lastSerial);    //prints time since program started

    //soil humidity
    analogReadHumidity();
    analogWriteHumidity();
  
    //temperature
    analogReadTemperature();
    analogWriteTemperature();
  
    //light
    analogReadLight();
    analogWriteLight();
  }
  bluetooth();
  bluetoothSerial();

}
