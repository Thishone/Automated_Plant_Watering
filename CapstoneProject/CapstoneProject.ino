/*
Castone Project

*/
#include <Arduino.h>
#include "blinkLed.h"
#include "analogInputOutput.h"
#include "waterPump.h"
#include "bluetooth.h"
#include "sonar.h"
#include <SoftwareSerial.h>

int baudRate = 9600;
unsigned long lastSerial = 0;

#define SET_PERIOD 2
#define READ_SENSORS_PERIOD   1000*SET_PERIOD

void setup() 
{
  Serial.begin(baudRate);              //  setup serial
  blinkLedSetup();
  waterPumpSetup();
  bluetoothSetup();
  sonarSetup();
}

// the loop function runs over and over again forever
void loop() 
{
  static int bt_status = BT_NONE;
  static int pump_status = PUMP_NONE;
  
  if ((millis() - lastSerial >= READ_SENSORS_PERIOD) 
      && (bt_status == BT_UNAVAILABLE)
      && (pump_status == PUMP_OFF))
  {
    lastSerial = millis();
    //Serial.println(lastSerial);    //prints time since program started

    //soil Moisture
    pump_status = ReadMoisture();
    //WriteMoisture();
  
    //temperature
    ReadTemperature();
    //WriteTemperature();
  
    //light
    ReadLight();
    //WriteLight(); 
  }

  if (pump_status == PUMP_ON)
  {
    sonar();
  }
  bt_status = bluetooth();
  bluetoothSerial();

}
