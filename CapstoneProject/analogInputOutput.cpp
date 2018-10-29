#include <Arduino.h>
#include "analogInputOutput.h"
#include "waterPump.h"
#include "blinkLed.h"

#define PERCENT 37  //ASCII code number "%"

// Data of Soil Moisture Sensor
//input voltages between 0 and 5 volts into integer values between 0 and 1023
#define MAX_INTEGER_VOLT_VALUE 1023

//Max raw value for 100% moisture is 800.
#define MAX_MOISTURE_VALUE 800.0

//Turn on/off Water Pump 
#define WATER_PUMP_THRESHOLD_VALUE 35.0

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
void ReadMoisture(void)
{
  ReadMoistureValue = analogRead(ReadMoisturePin);     // read the input pin

  soilMoistureRawVal = MAX_INTEGER_VOLT_VALUE - ReadMoistureValue;

  Serial.println("Moisture Value:");
  Serial.println(soilMoistureRawVal);

  if (soilMoistureRawVal < MAX_MOISTURE_VALUE)
  {
    soilMoisturePercentage = ((float)soilMoistureRawVal / MAX_MOISTURE_VALUE)*100.0;
    sprintf (sprintfBuffer, "Soil Moisture Percentage: %d%c \n",(int)soilMoisturePercentage,PERCENT);
    Serial.print (sprintfBuffer);
  }

  if (soilMoisturePercentage <= WATER_PUMP_THRESHOLD_VALUE){
      Serial.println(" => Turn on Water Pump");
      ledOn();
      waterPumpOn();
  } else {
      Serial.println(" => Turn off the Water Pump");
      ledOff();
      waterPumpOff();
  }
  Serial.println("\n");

  delay(500);
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
  delay(500);
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
//  Serial.println("Temperature Value:");
//  Serial.println(ReadTemperatureValue);             // debug value
  delay(500);
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
  delay(500);
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
//  Serial.println("Light Value:");
//  Serial.println(ReadLightValue);             // debug value
  delay(500);
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
  delay(500);
}
