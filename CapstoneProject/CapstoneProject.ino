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
#include "ezScrn.h"

//long baudRate = 115200;
int baudRate = 9600;
unsigned long lastSerial = 0;

#define SET_PERIOD 2
#define READ_SENSORS_PERIOD   1000*SET_PERIOD

int snar_status = SONAR_NONE;
int pump_status = PUMP_NONE;

boolean ezScrn_on = 1;

void setup() 
{
  if (ezScrn_on == 1){
    Serial.begin(115200);              //  setup serial
  } else {
    Serial.begin(9600);              //  setup serial
  }
  
  blinkLedSetup();
  waterPumpSetup();
  bluetoothSetup();
  sonarSetup();
  ezScrnSetup();
}

// the loop function runs over and over again forever
void loop() 
{
  static int bt_status = BT_UNAVAILABLE;
  if (ezScrn_on == 1)
  {
    ezScrn();
  }
  else
  {
    if (millis() - lastSerial >= READ_SENSORS_PERIOD) 
    {
      lastSerial = millis();
      //Serial.println(lastSerial);    //prints time since program started
      Serial.println("\n");
      
      //soil Moisture
      pump_status = ReadMoisture();
  
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

    }

  bt_status = bluetooth();
  //bluetoothSerial();
}
  
}
