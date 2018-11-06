#include <Arduino.h>
#include "analogInputOutput.h"
#include "waterPump.h"
#include "blinkLed.h"
#include "sonar.h"

extern int snar_status;

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

int soilMoistureRawVal = 0;
float soilMoisturePercentage = 0;

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

char sprintfBuffer[60]; // store messages

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
    sprintf (sprintfBuffer, "Soil Moisture Percentage: %d%c \n",(int)soilMoisturePercentage,PERCENT);
    Serial.print (sprintfBuffer);
  }

//  if (soilMoisturePercentage <= WATER_PUMP_THRESHOLD_VALUE){
//      ledOn();
//      if (snar_status == SONAR_OVER_LIMIT_DISTANCE){
//        Serial.println("Turn off Water Pump because the tank water is low");
//        retValue = waterPumpOff();
//      } else {
//        retValue = waterPumpOn();
//        Serial.print("Turn on Water Pump: ");
//        Serial.println(retValue);
//      }
//
//  } else {
//      ledOff();
//      retValue = waterPumpOff();
//      Serial.print("Turn off Water Pump: ");
//      Serial.println(retValue);      
//  }

//  Serial.println("\n");

//  delay(500);
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
    Serial.println("Turn off Water Pump because the tank water is low!!!");
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
    Serial.print("Diff moisture value (Max - Min): ");
    Serial.println(diff_moisture);      
    if (diff_moisture < 10){
      waterPumpOn();
      Serial.println("wait for 3 second");
      delay(3000);  // wait for a second
    } else if (diff_moisture >= 10 && diff_moisture < 20){
      waterPumpOn();
      Serial.println("wait for 5 second");
      delay(5000);
    } else if (diff_moisture >= 20 && diff_moisture < 30){
      waterPumpOn();
      Serial.println("wait for 10 second");
      delay(10000);
    } else if (diff_moisture >= 30 && diff_moisture < 50){
      waterPumpOn();
      Serial.println("wait for 15 second");
      delay(15000);
    } else if (diff_moisture >= 50){
      waterPumpOn();
      Serial.println("wait for 20 second");
      delay(20000);
    }
    waterPumpOff();
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
  Serial.print("Temperature Value:");
  Serial.println(ReadTemperatureValue);             // debug value
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
  Serial.print("Light Value:");
  Serial.println(ReadLightValue);             // debug value
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
