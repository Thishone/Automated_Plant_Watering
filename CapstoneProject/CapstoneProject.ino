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
#include "debugLog.h"

int baudRate = 9600;
unsigned long lastSerial = 0;

#define SET_PERIOD 2
#define READ_SENSORS_PERIOD   1000*SET_PERIOD

int snar_status = SONAR_NONE;
int pump_status = PUMP_NONE;

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
  static int bt_status = BT_UNAVAILABLE;
  
  if ((millis() - lastSerial >= READ_SENSORS_PERIOD) 
      )
  {
    lastSerial = millis();
    //Serial.println(lastSerial);    //prints time since program started
    
    Serial.println("\n");
    
    //soil Moisture
    pump_status = ReadMoisture();
    //WriteMoisture();

    if (bt_status & BT_AVAILABLE)
    {
      debugLog("bt_status: ", bt_status, NULL, DEBUG_DEV);
      if (bt_status & BT_READ_ON){
        waterPumpOn();
      } else if (bt_status & BT_READ_OFF){
        waterPumpOff();
      }
    } else {
      supplyWater();
    }
    
    //temperature
    //ReadTemperature();
  
    //light
    //ReadLight();

    snar_status = sonar();
//
//    if (snar_status == SONAR_OVER_LIMIT_DISTANCE)
//    {
//      waterPumpOff();
//      pump_status = PUMP_OFF;
//    }
  }

  bt_status = bluetooth();
  bluetoothSerial();
}
