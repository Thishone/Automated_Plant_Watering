#include <Arduino.h>
#include "analogInputOutput.h"
#include "waterPump.h"
#include "blinkLed.h"

// Data of Soil Humidity Sensor
//input voltages between 0 and 5 volts into integer values between 0 and 1023
#define MAX_INTEGER_VOLT_VALUE 1023

//Max raw value for 100% moisture is 800.
#define MAX_MOISTURE_VALUE 800

//Turn on Water Pump 
#define TRUR_ON_PUMP_THRESHOLD_VALUE 25

int soilMoistureRawVal = 0;
int soilMoisturePercentage = 0;
int analogReadHumidityPin = 0;     // connected to analog pin 0
                                   // outside leads to ground and +5V
int analogWriteHumidityPin = 8; 
int analogReadHumidityValue = 0;   // variable to store the value read

// Data of Temperature Sensor 
int analogReadTemperaturePin = 1;     // connected to analog pin 1

int analogWriteTemperaturePin = 9; 
int analogReadTemperatureValue = 0;   // variable to store the value read

// Data of Light Sensor 
int analogReadLightPin = 2;     // connected to analog pin 1

int analogWriteLightPin = 10; 
int analogReadLightValue = 0;   // variable to store the value read

/////////////////////////////////////////////////////////////////
// FUNCTION      : analogReadHumidity()
// DESCRIPTION   : This function reads the value of soil humidity
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void analogReadHumidity(void)
{
  analogReadHumidityValue = analogRead(analogReadHumidityPin);     // read the input pi

  soilMoistureRawVal = MAX_INTEGER_VOLT_VALUE - analogReadHumidityValue;

  if (soilMoistureRawVal < MAX_MOISTURE_VALUE){
    soilMoisturePercentage = (soilMoistureRawVal/MAX_MOISTURE_VALUE)*100;
  }

  if (soilMoisturePercentage <= TRUR_ON_PUMP_THRESHOLD_VALUE){
      Serial.println(" => Turn on Water Pump");
      ledOn();
      waterPumpOn();
  }
   else {
      Serial.println(" => Turn off the Water Pump");
      ledOff();
      waterPumpOff();
  }
//  Serial.println("Humidity Value:");
//  Serial.println(analogReadHumidityValue);             // debug value
//    if (analogReadHumidityValue > 512)
//    {
//      Serial.println(" => Turn on the water pump");
//      waterPumpOn();
//    }
//    else {
//      Serial.println(" => Turn off the water pump");
//      waterPumpOff();
//    }
  delay(500);
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : analogWriteHumidity()
// DESCRIPTION   : This function writes the value of soil humidity
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void analogWriteHumidity(void)
{
  analogWrite(analogWriteHumidityPin, analogReadHumidityValue);
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
  Serial.println("Temperature Value:");
  Serial.println(analogReadTemperatureValue);             // debug value
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
  Serial.println("Light Value:");
  Serial.println(analogReadLightValue);             // debug value
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
