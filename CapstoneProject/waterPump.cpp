/*
 * waterPump.cpp
 *
 *  Created on: Nov 15, 2018
 *      Author: Jin Taek Lee, Thishone Wijayakumar, Ajo Cherian Thomas
 */
#include <Arduino.h>
#include "waterPump.h"
#include "blinkLed.h"
#include "analogInputOutput.h"
#include "debugLog.h"

const int waterPumpPin =  11;// the number of the water pump pin

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
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : waterPumpOn()
// DESCRIPTION   : This function turn on the water pump
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
int waterPumpOn(void)
{
  int retValue = PUMP_NONE;
  if (alertWaterIsLow() == 0){
    digitalWrite(waterPumpPin, HIGH);   // turn the water pump on (HIGH is the voltage level)
    //debugLog("water Pump On!", NONE_DATA, NULL, SCRN_OUTA);
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
  int retValue = PUMP_NONE;
  digitalWrite(waterPumpPin, LOW);    // turn the water pump off by making the voltage LOW
  //debugLog("water Pump Off!", NONE_DATA, NULL, SCRN_OUTA);
#ifdef LED_FEATURE
  ledOff();
#endif
  retValue = PUMP_OFF;
  return retValue;
}
