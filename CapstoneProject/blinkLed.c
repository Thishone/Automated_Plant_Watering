/*
 * blinkLed.c
 *
 *  Created on: Nov 15, 2018
 *      Author: Jin Taek Lee, Thishone Wijayakumar, Ajo Cherian Thomas
 */


#include <Arduino.h>
#include "blinkLed.h"

#ifdef LED_FEATURE

const int ledPin =  13;// the number of the LED pin
const int ledGreenPin =  12;
const int ledYellowPin =  11;
const int ledRedPin =  10;

/////////////////////////////////////////////////////////////////
// FUNCTION      : blinkLedSetup()
// DESCRIPTION   : This function sets LED pin
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void blinkLedSetup(void)
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ledPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledYellowPin, OUTPUT);
  pinMode(ledRedPin, OUTPUT);  
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : blinkOn()
// DESCRIPTION   : This function turns on LED
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void ledOn(void)
{
    digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : blinkOff()
// DESCRIPTION   : This function turns off LED
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void ledOff(void)
{
    digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : blinkGreenOn()
// DESCRIPTION   : This function turns on LED
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void blinkGreenOn(void)
{
    digitalWrite(ledGreenPin, HIGH);   // turn the LED on (HIGH is the voltage level)
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : blinkGreenOff()
// DESCRIPTION   : This function turns off LED
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void blinkGreenOff(void)
{
    digitalWrite(ledGreenPin, LOW);    // turn the LED off by making the voltage LOW
}


/////////////////////////////////////////////////////////////////
// FUNCTION      : blinkYellowOn()
// DESCRIPTION   : This function turns on LED
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void blinkYellowOn(void)
{
    digitalWrite(ledYellowPin, HIGH);   // turn the LED on (HIGH is the voltage level)
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : blinkYellowOff()
// DESCRIPTION   : This function turns off LED
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void blinkYellowOff(void)
{
    digitalWrite(ledYellowPin, LOW);    // turn the LED off by making the voltage LOW
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : blinkRedOn()
// DESCRIPTION   : This function turns on LED
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void blinkRedOn(void)
{
    digitalWrite(ledRedPin, HIGH);   // turn the LED on (HIGH is the voltage level)
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : blinkRedOff()
// DESCRIPTION   : This function turns off LED
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void blinkRedOff(void)
{
    digitalWrite(ledRedPin, LOW);    // turn the LED off by making the voltage LOW
}
/////////////////////////////////////////////////////////////////
// FUNCTION      : blinkOnOff()
// DESCRIPTION   : This function turns on and off LED
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void blinkOnOff(void)
{
    digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);                       // wait for a second
}
#endif
