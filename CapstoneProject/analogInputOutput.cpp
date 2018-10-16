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

//Turn on Water Pump 
#define TRUR_ON_PUMP_THRESHOLD_VALUE 35.0

int soilMoistureRawVal = 0;
float soilMoisturePercentage = 0;

int analogReadMoisturePin = 0;     // connected to analog pin 0
                                   // outside leads to ground and +5V
int analogWriteMoisturePin = 8; 
int analogReadMoistureValue = 0;   // variable to store the value read

// Data of Temperature Sensor 
int analogReadTemperaturePin = 1;     // connected to analog pin 1

int analogWriteTemperaturePin = 9; 
int analogReadTemperatureValue = 0;   // variable to store the value read

// Data of Light Sensor 
int analogReadLightPin = 2;     // connected to analog pin 1

int analogWriteLightPin = 10; 
int analogReadLightValue = 0;   // variable to store the value read

char buffer[60]; // store messages

/////////////////////////////////////////////////////////////////
// FUNCTION      : analogReadMoisture()
// DESCRIPTION   : This function reads the value of soil Moisture
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void analogReadMoisture(void)
{
  analogReadMoistureValue = analogRead(analogReadMoisturePin);     // read the input pin

  soilMoistureRawVal = MAX_INTEGER_VOLT_VALUE - analogReadMoistureValue;

  Serial.println("Moisture Value:");
  Serial.println(soilMoistureRawVal);

  if (soilMoistureRawVal < MAX_MOISTURE_VALUE)
  {
    soilMoisturePercentage = ((float)soilMoistureRawVal / MAX_MOISTURE_VALUE)*100.0;
    sprintf (buffer, "Soil Moisture Percentage: %d%c \n",(int)soilMoisturePercentage,PERCENT);
    Serial.print (buffer);
  }

  if (soilMoisturePercentage <= TRUR_ON_PUMP_THRESHOLD_VALUE){
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
// FUNCTION      : analogWriteMoisture()
// DESCRIPTION   : This function writes the value of soil Moisture
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void analogWriteMoisture(void)
{
  analogWrite(analogWriteMoisturePin, analogReadMoistureValue);
  delay(500);
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : analogReadTemperature()
// DESCRIPTION   : This function reads the value of soil temperature
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void analogReadTemperature(void)
{
  analogReadTemperatureValue = analogRead(analogReadTemperaturePin);     // read the input pi
//  Serial.println("Temperature Value:");
//  Serial.println(analogReadTemperatureValue);             // debug value
  delay(500);
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : analogWriteTemperature()
// DESCRIPTION   : This function writes the value of temperature
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void analogWriteTemperature(void)
{
  analogWrite(analogWriteTemperaturePin, analogReadTemperatureValue);
  delay(500);
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : analogReadLight()
// DESCRIPTION   : This function reads the value of soil light
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void analogReadLight(void)
{
  analogReadLightValue = analogRead(analogReadLightPin);     // read the input pi
//  Serial.println("Light Value:");
//  Serial.println(analogReadLightValue);             // debug value
  delay(500);
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : analogWriteLight()
// DESCRIPTION   : This function writes the value of light
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void analogWriteLight(void)
{
  analogWrite(analogWriteLightPin, analogReadLightValue);
  delay(500);
}
