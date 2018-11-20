/*
 * analogInputOutput.cpp
 *
 *  Created on: Nov 15, 2018
 *      Author: Jin Taek Lee, Thishone Wijayakumar, Ajo Cherian Thomas
 */
#include <Arduino.h>
#include "analogInputOutput.h"
#include "waterPump.h"
#include "blinkLed.h"
#include "sonar.h"
#include "debugLog.h"
#include "ezScrn.h"

extern int snar_status;
extern boolean newData;

extern int learnTest;

//#define PERCENT 37  //ASCII code number "%"

// Data of Soil Moisture Sensor
//input voltages between 0 and 5 volts into integer values between 0 and 1023
#define MAX_INTEGER_VOLT_VALUE 600 //1023

//Max raw value for 100% moisture is 800.
#define MAX_MOISTURE_VALUE 280.0 //800.0

//Turn on/off Water Pump 
#define WATER_PUMP_THRESHOLD_VALUE 35.0

//read the setted value from bluetooth by user
unsigned int max_moisture = 0;
unsigned int min_moisture = 0;
unsigned int diff_moisture = 0;
unsigned int old_diff_moisture = 0;

int soilMoistureRawVal = 0;
float soilMoisturePercentage = 0;
float old_soilMoisturePercentage = 100;

const int ReadMoisturePin = 0;     // connected to analog pin 0
                                   // outside leads to ground and +5V
const int WriteMoisturePin = 8; 
int ReadMoistureValue = 0;   // variable to store the value read

// Data of Temperature Sensor 
const int ReadTemperaturePin = 1;     // connected to analog pin 1

const int WriteTemperaturePin = 9; 
int ReadTemperatureValue = 0;   // variable to store the value read
int old_ReadTemperatureValue = 0;

// Data of Light Sensor 
const int ReadLightPin = 2;     // connected to analog pin 1

const int WriteLightPin = 10; 
int ReadLightValue = 0;   // variable to store the value read
int old_ReadLightValue = 100;

int waterPumpTime=0;

void setMaxMoistureValue(int max)
{
  max_moisture = max;
}

void setMinMoistureValue(int min)
{
  min_moisture = min;
}
/////////////////////////////////////////////////////////////////
// FUNCTION      : ReadMoisture()
// DESCRIPTION   : This function reads the value of soil Moisture
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
int ReadMoisture(void)
{
  int retValue = 0;
  
  ReadMoistureValue = analogRead(ReadMoisturePin);     // read the input pin

  soilMoistureRawVal = MAX_INTEGER_VOLT_VALUE - ReadMoistureValue;

  if (soilMoistureRawVal < MAX_MOISTURE_VALUE)
  {
    soilMoisturePercentage = ((float)soilMoistureRawVal / MAX_MOISTURE_VALUE)*100.0;

    debugLog("Soil Moisture: ", soilMoisturePercentage, NULL, SCRN_OUT_MOISTURE);
  }

  return retValue;
}
/////////////////////////////////////////////////////////////////
// FUNCTION      : alertWaterIsLow()
// DESCRIPTION   : This function alert the tank water is low
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
int alertWaterIsLow(void)
{
  int retValue = 0;
  if (snar_status == SONAR_OVER_LIMIT_DISTANCE){
    debugLog("Turn off Water Pump because the tank water is low!!!", NONE_DATA, NULL, SCRN_OUTA);
    retValue = 1;
  }
  return retValue;
}
/////////////////////////////////////////////////////////////////
// FUNCTION      : learnSupplyWater()
// DESCRIPTION   : This function supplys Water
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void learnSupplyWater(void)
{
  static int waitSecondAfterPump = 0;
  static int measurePotSize = 0;
  
  if ((soilMoisturePercentage - old_soilMoisturePercentage <= 10))
  {  
    if (waitSecondAfterPump == 0)
    {
      debugLog("Learn supplyWater ", NONE_DATA, NULL, SCRN_OUTA);
      waterPumpOn();
      delay(3000);
      debugLog("wait for 3 second", NONE_DATA, NULL, SCRN_OUTA);
      waterPumpOff();
      waitSecondAfterPump = 10;
    
      old_soilMoisturePercentage = soilMoisturePercentage;
      
      measurePotSize ++;
      debugLog("measurePotSize ", measurePotSize, NULL, SCRN_OUTA);
    } else {
      waitSecondAfterPump --;
      debugLog("wait After Pump ", waitSecondAfterPump, NULL, SCRN_OUTA);
    }
  } else {
    waterPumpTime = measurePotSize * 3000;
    learnTest = 0;
    debugLog("water Pump Time ", waterPumpTime, NULL, SCRN_OUTA);
  }
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : supplyWater()
// DESCRIPTION   : This function supplys Water
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void supplyWater(void)
{
  static int waitSecondAfterPump = 0;
  
  debugLog("Regular supplyWater ", NONE_DATA, NULL, SCRN_OUTA);
  //if (soilMoisturePercentage <= min_moisture)
  if ((soilMoisturePercentage - old_soilMoisturePercentage <= 10))
  {
    if (waitSecondAfterPump == 0)
    {
      debugLog("Regular supplyWater ", NONE_DATA, NULL, SCRN_OUTA);
      waterPumpOn();
      debugLog("wait for 3 second", NONE_DATA, NULL, SCRN_OUTA);
      delay(3000);
      //delay(waterPumpTime);  // wait for a second
      
      waterPumpOff();
      waitSecondAfterPump = 10;
    } else {
      waitSecondAfterPump --;
      debugLog("wait After Pump ", waitSecondAfterPump, NULL, SCRN_OUTA);
    }
  } 
}
/////////////////////////////////////////////////////////////////
// FUNCTION      : WriteMoisture()
// DESCRIPTION   : This function writes the value of soil Moisture
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void WriteMoisture(void)
{
  analogWrite(WriteMoisturePin, ReadMoistureValue);
//  delay(500);
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : ReadTemperature()
// DESCRIPTION   : This function reads the value of soil temperature
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void ReadTemperature(void)
{
  ReadTemperatureValue = analogRead(ReadTemperaturePin);     // read the input pin
  if (old_ReadTemperatureValue != ReadTemperatureValue){
    debugLog("Temperature Value: ", ReadTemperatureValue, NULL, SCRN_OUT_TEMPERATURE);
    old_ReadTemperatureValue = ReadTemperatureValue;
  }
//  delay(500);
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : WriteTemperature()
// DESCRIPTION   : This function writes the value of temperature
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void WriteTemperature(void)
{
  analogWrite(WriteTemperaturePin, ReadTemperatureValue);
//  delay(500);
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : ReadLight()
// DESCRIPTION   : This function reads the value of soil light
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void ReadLight(void)
{
  ReadLightValue = analogRead(ReadLightPin);     // read the input pin
  if (old_ReadLightValue != ReadLightValue){
    debugLog("Light Value: ", ReadLightValue, NULL, SCRN_OUT_LIGHT);
    old_ReadLightValue = ReadLightValue;
  }
//  delay(500);
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : WriteLight()
// DESCRIPTION   : This function writes the value of light
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void WriteLight(void)
{
  analogWrite(WriteLightPin, ReadLightValue);
//  delay(500);
}
