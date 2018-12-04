/*
 * sensors.cpp
 *
 *  Created on: Nov 15, 2018
 *      Author: Jin Taek Lee, Thishone Wijayakumar, Ajo Cherian Thomas
 */
#include <Arduino.h>
#include "dht.h"
#include "sensors.h"
#include "waterPump.h"
#include "blinkLed.h"
#include "sonar.h"
#include "debugLog.h"
#include "ezScrn.h"

extern boolean newData;
extern boolean learningPotSize;
extern boolean normalWatering;
#ifdef TEST_CODE
boolean testError = false;
#endif
dht DHT;

// Data of Soil Moisture Sensor
//input voltages between 0 and 5 volts into integer values between 0 and 600023
#define MAX_MOISTURE_INTEGER_VOLT_VALUE 600
//Max raw value for 100% moisture is 280.
#define MAX_MOISTURE_VALUE 280.0

#define MAX_OVERFLOW_INTEGER_VOLT_VALUE 1023
//Max raw value for 100% moisture is 800.
#define MAX_OVERFLOW_VALUE 800.0

//Turn on/off Water Pump 
#define WATER_PUMP_THRESHOLD_VALUE 35.0

#define ONE_MINUTE 10
#define ONE_SECOND 1000
#define TREE_SECONDS 3000

//read the setted value from bluetooth by user
unsigned int max_moisture = 0;
unsigned int min_moisture = 0;
unsigned int diff_moisture = 0;
unsigned int old_diff_moisture = 0;

float soilMoisturePercentage = 0;
float old_soilMoisturePercentage = 100;

// DHT11 Temperature and humidity sensor 
#define DHT11_PIN 7

// Data of Moisture Sensor 
const int ReadMoisturePin = 0;     // connected to analog pin 0

// Data of Light Sensor 
const int ReadLightPin = 2;     // connected to analog pin 1
#define SUN_LIGHT  850
#define LOW_LIGHT 400


// Data of Overflow Sensor 
const int ReadOverflowPin = 3;     // connected to analog pin 0

int wateringTime=0;
int waitWateringTime = 10;
int wait1MinuteAfterWatering = 0;
boolean underMin = false;
boolean overMax = false;
boolean PumpOn = false;
/////////////////////////////////////////////////////////////////
// FUNCTION      : setMaxMoistureValue()
// DESCRIPTION   : 
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void setMaxMoistureValue(int max)
{
  max_moisture = max;
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : ReadMsetMinMoistureValueoisture()
// DESCRIPTION   : 
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
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
  int ReadMoistureValue = 0;   // variable to store the value read
  int soilMoistureRawVal = 0;
  
  ReadMoistureValue = analogRead(ReadMoisturePin);     // read the input pin

  soilMoistureRawVal = MAX_MOISTURE_INTEGER_VOLT_VALUE - ReadMoistureValue;

  if (soilMoistureRawVal < MAX_MOISTURE_VALUE)
  {
    soilMoisturePercentage = ((float)soilMoistureRawVal / MAX_MOISTURE_VALUE)*100.0;
    debugLog("Soil Moisture(%): ", soilMoisturePercentage, NULL, SCRN_OUT_MOISTURE);
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
  int disp_wateringTime = 0;
//  debugLog("soilMoisturePercentage ", soilMoisturePercentage, NULL, SCRN_OUTA);
//  debugLog("old_soilMoisturePercentage ", old_soilMoisturePercentage, NULL, SCRN_OUTA);
  if ((soilMoisturePercentage - old_soilMoisturePercentage <= 10))
  {  
    if (waitSecondAfterPump == 0)
    {
      debugLog("Learn supplyWater ", NONE_DATA, NULL, SCRN_OUTA);
      waterPumpOn();
      delay(TREE_SECONDS);
      debugLog("wait second: ", TREE_SECONDS, NULL, SCRN_OUTA);
      waterPumpOff();
      waitSecondAfterPump = ONE_MINUTE;
    
      old_soilMoisturePercentage = soilMoisturePercentage;
      //old_soilMoisturePercentage = 50; for test
      measurePotSize ++;
      //debugLog("measurePotSize ", measurePotSize, NULL, SCRN_OUTA);
    } else {
      waitSecondAfterPump --;
      debugLog("Learning Wait for seconds: ", waitSecondAfterPump, NULL, SCRN_OUTA);
    }
  } else {
    wateringTime = measurePotSize * TREE_SECONDS;
    disp_wateringTime = wateringTime /1000;
    learningPotSize = false;
    debugLog("Watering Pump Time: ", disp_wateringTime, NULL, SCRN_OUT_WATERING_TIME);
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
  if (wait1MinuteAfterWatering == 0){
    if ((soilMoisturePercentage <= min_moisture) && (underMin == false)){
      underMin = true;
      overMax = false;
    } else if (soilMoisturePercentage >= max_moisture){
      debugLog("Over Max ", NONE_DATA, NULL, SCRN_OUTA);
      waterPumpOff();
//      overMax = true;
//      underMin = false;
//      waitWateringTime = 0;
      initVariabls();
    }
      
    if (underMin == true)
    {
      if (PumpOn == false){
        debugLog("Under Min ", NONE_DATA, NULL, SCRN_OUTA);
        waterPumpOn();
        waitWateringTime = wateringTime/ONE_SECOND;
        debugLog("Watering Time: ", wateringTime, NULL, SCRN_OUTA);
        PumpOn = true;
      }
      
      if (waitWateringTime == 0)
      {
        debugLog("pump off & second 0 ", NONE_DATA, NULL, SCRN_OUTA);      
        waterPumpOff();
        PumpOn = false;
        wait1MinuteAfterWatering = ONE_MINUTE;
        //underMin = false;
      } else {
        waitWateringTime --;
        debugLog("Watering Wait for seconds: ", waitWateringTime, NULL, SCRN_OUTA);
        if (overMax == true){
          waitWateringTime = 0;
        }
      }
    } 
  } else {
    wait1MinuteAfterWatering --;
    debugLog("Wait 1 Minute: ", wait1MinuteAfterWatering, NULL, SCRN_OUTA);
  }
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : clearTime()
// DESCRIPTION   : This function supplys clearTime
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void initVariabls(void)
{
  //debugLog("Init Variabls ", NONE_DATA, NULL, SCRN_OUTA);
  //normalWatering = false;
  waitWateringTime = 0;
  wait1MinuteAfterWatering = 0;
  underMin = false;
  overMax = false;
  PumpOn = false;
}
/////////////////////////////////////////////////////////////////
// FUNCTION      : DHT11_HumiditySensor()
// DESCRIPTION   : This function reads the value of Humidity
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void DHT11_HumiditySensor(void)
{
  int ReadHumidityValue = DHT.read11(DHT11_PIN);

  debugLog("Temperature(°C): ", DHT.temperature, NULL, SCRN_OUT_TEMPERATURE);
  debugLog("Humidity(%): ", DHT.humidity, NULL, SCRN_OUT_HUMIDITY);
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : ReadLight()
// DESCRIPTION   : This function reads the value of soil light
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void ReadLight(void)
{
  int ReadLightValue = 0;
  ReadLightValue = analogRead(ReadLightPin);     // read the input pin

  if (ReadLightValue >= SUN_LIGHT){
    debugLog("Sun light: ", ReadLightValue, NULL, SCRN_OUT_LIGHT);
  } else if ((ReadLightValue < SUN_LIGHT)&& (ReadLightValue >= LOW_LIGHT)){
    debugLog("Indoor light: ", ReadLightValue, NULL, SCRN_OUT_LIGHT);
  } else if (ReadLightValue < LOW_LIGHT){
    debugLog("Low light: ", ReadLightValue, NULL, SCRN_OUT_LIGHT);
  }
    
}


/////////////////////////////////////////////////////////////////
// FUNCTION      : ReadOverflow()
// DESCRIPTION   : This function reads the value of soil Moisture
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void ReadOverflow(void)
{
  int ReadOverflowValue = 0;   // variable to store the value read
  int soilOverflowRawVal = 0;
  float soilOverflowPercentage = 0;
  
  ReadOverflowValue = analogRead(ReadOverflowPin);     // read the input pin


  soilOverflowRawVal = MAX_OVERFLOW_INTEGER_VOLT_VALUE - ReadOverflowValue;
  
  //debugLog("soilOverflowRawVal: ", soilOverflowRawVal, NULL, SCRN_OUTA);

  if (soilOverflowRawVal <= MAX_OVERFLOW_INTEGER_VOLT_VALUE)
  {
    soilOverflowPercentage = ((float)soilOverflowRawVal / MAX_OVERFLOW_VALUE)*100.0;
#ifdef TEST_CODE
    soilOverflowPercentage = 10;
//    if (testError == true){
//      soilOverflowPercentage = 20;
//    }
#endif
    if (soilOverflowPercentage >= 15){
      debugLog("Overflow Pump Stop(%): ", soilOverflowPercentage, NULL, SCRN_OUT_OVERFLOW);
      waterPumpOff();
      initVariabls();
    } else {
      debugLog("Dry wet(%): ", soilOverflowPercentage, NULL, SCRN_OUT_OVERFLOW);
    }
  }
}
