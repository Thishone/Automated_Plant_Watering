/*
 * waterPump.cpp
 *
 *  Created on: Nov 15, 2018
 *      Author: Jin Taek Lee, Thishone Wijayakumar, Ajo Cherian Thomas
 */
#include <Arduino.h>
#include "waterPump.h"
#include "blinkLed.h"
#include "sensors.h"
#include "debugLog.h"
#include "sonar.h"

extern sonar_st snar_status;

const int waterPumpPin =  2;// the number of the water pump pin

/////////////////////////////////////////////////////////////////
// FUNCTION      : waterPumpSetup()
// DESCRIPTION   : This function sets the warter pump pin
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void waterPumpSetup(void)
{
  // initialize digital pin waterPump as an output.
  pinMode(waterPumpPin, OUTPUT);
  digitalWrite(waterPumpPin, HIGH);
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : waterPumpOn()
// DESCRIPTION   : This function turn on the water pump
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
int waterPumpOn(void)
{
  waterPump_st retValue = PUMP_NONE;
  if (alertWaterIsLow() == 0){
    //digitalWrite(waterPumpPin, HIGH);   // turn the water pump on (HIGH is the voltage level)
    digitalWrite(waterPumpPin, LOW);   // turn the water pump on (HIGH is the voltage level)
    debugLog("water Pump On", NONE_DATA, NULL, SCRN_OUTA);
#ifdef LED_FEATURE
    ledOn();
#endif
    retValue = PUMP_ON;
  } else {
    retValue = PUMP_OFF;
  }
  return retValue;
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : waterPumpOff()
// DESCRIPTION   : This function turn off the water pump
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
int waterPumpOff(void)
{
  waterPump_st retValue = PUMP_NONE;
  //digitalWrite(waterPumpPin, LOW);    // turn the water pump off by making the voltage LOW
  digitalWrite(waterPumpPin, HIGH);    // turn the water pump off by making the voltage LOW
  //debugLog("water Pump Off", NONE_DATA, NULL, SCRN_OUTA);
#ifdef LED_FEATURE
  ledOff();
#endif
  retValue = PUMP_OFF;
  return retValue;
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : alertWaterIsLow()
// DESCRIPTION   : This function alert the tank water is low
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
boolean alertWaterIsLow(void)
{
  boolean retValue = false;
  if (snar_status == SONAR_OVER_LIMIT_DISTANCE){
    debugLog("Turn off Water Pump because the water tank is low!!!", NONE_DATA, NULL, SCRN_OUTA);
    retValue = true;
  }
  return retValue;
}
