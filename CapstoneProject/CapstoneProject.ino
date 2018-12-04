/*
 * CapstoneProject.cpp
 *
 *  Created on: Nov 15, 2018
 *      Author: Jin Taek Lee, Thishone Wijayakumar, Ajo Cherian Thomas
 */
#include <Arduino.h>
#include "blinkLed.h"
#include "sensors.h"
#include "waterPump.h"
#include "bluetooth.h"
#include "sonar.h"
#include <SoftwareSerial.h>
#include "debugLog.h"
#include "ezScrn.h"

unsigned long lastSerial = 0;

#define READ_SENSORS_PERIOD   2000

sonar_st snar_status = SONAR_NONE;

boolean learningPotSize = false;
boolean normalWatering = false;

void sensorsOperation(void);

void setup() 
{

  Serial.begin(115200);              //  setup serial
  ezScrnSetup();

#ifdef LED_FEATURE
  blinkLedSetup();
#endif
  waterPumpSetup();
#ifdef BLUETOOTH_FEATURE
  bluetoothSetup();
#endif
  sonarSetup();
}


/////////////////////////////////////////////////////////////////
// FUNCTION      : loop()
// DESCRIPTION   : the loop function runs over and over again forever
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void loop() 
{
  sensorsOperation();
  //delay(1000);
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : sensorsOperation()
// DESCRIPTION   : 
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void sensorsOperation(void)
{
  #ifdef BLUETOOTH_FEATURE
  static int bt_status = BT_UNAVAILABLE;
  #endif
  
  if (millis() - lastSerial >= READ_SENSORS_PERIOD) 
  {
    lastSerial = millis();
    
    ezScrn();
    
    //soil Moisture
    ReadMoisture();
    
    if (learningPotSize == true){
      learnSupplyWater();
    } else {
      if (normalWatering == true) {
        supplyWater();
      }       
    }
    

    snar_status = sonar();
    if (snar_status == SONAR_OVER_LIMIT_DISTANCE){
      initVariabls();
      waterPumpOff();
    }
    
    //Humidity
    DHT11_HumiditySensor();
    
    //light
    ReadLight();

    if (learningPotSize == false){
      ReadOverflow();
    }

    if (alertWaterIsLow() == true){
      initVariabls();
      waterPumpOff();
    }
  }
}
