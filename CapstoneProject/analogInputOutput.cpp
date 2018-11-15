#include <Arduino.h>
#include "analogInputOutput.h"
#include "waterPump.h"
#include "blinkLed.h"
#include "sonar.h"
#include "debugLog.h"
#include "ezScrn.h"

extern int snar_status;
extern boolean newData;

#define PERCENT 37  //ASCII code number "%"

// Data of Soil Moisture Sensor
//input voltages between 0 and 5 volts into integer values between 0 and 1023
#define MAX_INTEGER_VOLT_VALUE 1023

//Max raw value for 100% moisture is 800.
#define MAX_MOISTURE_VALUE 800.0

//Turn on/off Water Pump 
#define WATER_PUMP_THRESHOLD_VALUE 35.0

//read the setted value from bluetooth by user
unsigned int  max_moisture = 35;
unsigned int  min_moisture = 35;
unsigned int  diff_moisture = 0;
unsigned int  pre_diff_moisture = 0;

int soilMoistureRawVal = 0;
float soilMoisturePercentage = 0;
float pre_soilMoisturePercentage = 0;

int ReadMoisturePin = 0;     // connected to analog pin 0
                                   // outside leads to ground and +5V
int WriteMoisturePin = 8; 
int ReadMoistureValue = 0;   // variable to store the value read

// Data of Temperature Sensor 
int ReadTemperaturePin = 1;     // connected to analog pin 1

int WriteTemperaturePin = 9; 
int ReadTemperatureValue = 0;   // variable to store the value read

// Data of Light Sensor 
int ReadLightPin = 2;     // connected to analog pin 1

int WriteLightPin = 10; 
int ReadLightValue = 0;   // variable to store the value read


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
    
    if ((int)pre_soilMoisturePercentage != (int)soilMoisturePercentage){
      debugLog("Soil Moisture: ", soilMoisturePercentage, NULL, DEBUG_DEV, SCRN_OUT_MOISTURE);
      pre_soilMoisturePercentage = soilMoisturePercentage;
    }
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
    debugLog("Turn off Water Pump because the tank water is low!!!", NONE_DATA, NULL, DEBUG_DEV, SCRN_OUTA);
    retValue = 1;
  }
  return retValue;
}
/////////////////////////////////////////////////////////////////
// FUNCTION      : supplyWater()
// DESCRIPTION   : This function supplys Water
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void supplyWater(void)
{
  if (soilMoisturePercentage <= min_moisture)
  {
    diff_moisture = max_moisture - min_moisture;
    if (pre_diff_moisture != diff_moisture){
      debugLog("Diff moisture value (Max - Min): ", diff_moisture, NULL, DEBUG_DEV, SCRN_OUTA);
    }

    if (diff_moisture < 10){
      waterPumpOn();
      debugLog("wait for 3 second", NONE_DATA, NULL, DEBUG_DEV, SCRN_OUTA);
      delay(3000);  // wait for a second
    } else if (diff_moisture >= 10 && diff_moisture < 20){
      waterPumpOn();
      debugLog("wait for 5 second", NONE_DATA, NULL, DEBUG_DEV, SCRN_OUTA);
      delay(5000);
    } else if (diff_moisture >= 20 && diff_moisture < 30){
      waterPumpOn();
      debugLog("wait for 10 second", NONE_DATA, NULL, DEBUG_DEV, SCRN_OUTA);
      delay(10000);
    } else if (diff_moisture >= 30 && diff_moisture < 50){
      waterPumpOn();
      debugLog("wait for 15 second", NONE_DATA, NULL, DEBUG_DEV, SCRN_OUTA);
      delay(15000);
    } else if (diff_moisture >= 50){
      waterPumpOn();
      debugLog("wait for 20 second", NONE_DATA, NULL, DEBUG_DEV, SCRN_OUTA);
      delay(20000);
    }
    waterPumpOff();
    debugLog("wait for 10 second", NONE_DATA, NULL, DEBUG_DEV, SCRN_OUTA);
    delay(10000);
  }
  else if (soilMoisturePercentage >= max_moisture)
  {
    waterPumpOff();
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
  ReadTemperatureValue = analogRead(ReadTemperaturePin);     // read the input pi
  debugLog("Temperature Value: ", ReadTemperatureValue, NULL, DEBUG_DEV, SCRN_OUT_TEMPERATURE);
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
  ReadLightValue = analogRead(ReadLightPin);     // read the input pi
  debugLog("Light Value: ", ReadLightValue, NULL, DEBUG_DEV, SCRN_OUT_LIGHT);
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
