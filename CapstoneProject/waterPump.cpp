#include <Arduino.h>
#include "waterPump.h"

const int waterPumpPin =  11;// the number of the water pump pin

void waterPumpSetup(void)
{
  // initialize digital pin waterPump as an output.
  pinMode(waterPumpPin, OUTPUT);
}

int waterPumpOn(void)
{
  int retValue = PUMP_NONE;
  digitalWrite(waterPumpPin, HIGH);   // turn the water pump on (HIGH is the voltage level)
  //delay(1000);                       // wait for a second
  retValue = PUMP_ON;
  return retValue;
}

int waterPumpOff(void)
{
  int retValue = PUMP_NONE;
  digitalWrite(waterPumpPin, LOW);    // turn the water pump off by making the voltage LOW
  //delay(1000);                       // wait for a second
  retValue = PUMP_OFF;
  return retValue;
}
