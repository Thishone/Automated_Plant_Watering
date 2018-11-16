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
//int baudRate = 9600;
unsigned long lastSerial = 0;

#define READ_SENSORS_PERIOD   2000

int snar_status = SONAR_NONE;
int pump_status = PUMP_NONE;

//boolean ezScrn_on = 1;

void sensorsOperation(void);

void setup() 
{
  //if (ezScrn_on == 1){
    Serial.begin(115200);              //  setup serial
    ezScrnSetup();
  //} else {
  //  Serial.begin(9600);              //  setup serial
  //}
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
  ezScrn();
  sensorsOperation();
}

void sensorsOperation(void){
#ifdef BLUETOOTH_FEATURE
  static int bt_status = BT_UNAVAILABLE;
#endif

  if (millis() - lastSerial >= READ_SENSORS_PERIOD) 
  {
    lastSerial = millis();
    
    //soil Moisture
    pump_status = ReadMoisture();

    supplyWater();

    snar_status = sonar();
    
    //temperature
    ReadTemperature();
  
    //light
    ReadLight();
  }
  //bt_status = bluetooth();
}
