/*
 * CapstoneProject.cpp
 *
 *  Created on: Nov 15, 2018
 *      Author: Jin Taek Lee, Thishone Wijayakumar, Ajo Cherian Thomas
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

unsigned long lastSerial = 0;

#define READ_SENSORS_PERIOD   2000

int snar_status = SONAR_NONE;
int pump_status = PUMP_NONE;

int learnTest = 1;

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

// the loop function runs over and over again forever
void loop() 
{
  //ezScrn();
  sensorsOperation();
}

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
    pump_status = ReadMoisture();
    
    if (learnTest == 1){
      learnSupplyWater();
    } else {
      supplyWater();
    }
    
    //snar_status = sonar();
    
    //temperature
    ReadTemperature();
    
    //light
    ReadLight();
  }
  //bt_status = bluetooth();
}
