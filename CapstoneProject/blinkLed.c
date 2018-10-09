#include <Arduino.h>
#include "blinkLed.h"

const int ledPin =  12;// the number of the LED pin

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
