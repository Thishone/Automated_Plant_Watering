/*
 * sonar.cpp
 *
 *  Created on: Nov 15, 2018
 *      Author: Jin Taek Lee, Thishone Wijayakumar, Ajo Cherian Thomas
 */
#include <Arduino.h>
#include "sonar.h"
#include "debugLog.h"
#include "blinkLed.h"
#include "sensors.h"

#ifdef TEST_CODE
extern boolean testError;
#endif

// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;

// defines variables
long duration;

//int old_sonarDistance = 0;


//1. If water level > 10cm, GREEN
//2. If 5 cm < water level > 10cm, YELLOW
//3. If water level < 5cm, RED and send message to refill water. Do not pump water if below 5cm.

//#define LIMIT_DISTANCE       15
#define FULL_WATER_LEVEL     13//20
#define HIGH_WATER_LEVEL     9//10
#define LOW_WATER_LEVEL      5
#define SPEED_SOUND 0.034

/////////////////////////////////////////////////////////////////
// FUNCTION      : sonarSetup()
// DESCRIPTION   : 
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void sonarSetup(void)
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : sonar()
// DESCRIPTION   : 
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
sonar_st sonar(void)
{
  sonar_st retValue = SONAR_NONE;
  int measureDistance = 0;
  int sonarDistance = 0;
  
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the sonarDistance
  sonarDistance = duration*SPEED_SOUND/2;

  measureDistance = FULL_WATER_LEVEL - sonarDistance;
  if (measureDistance > 0){
  #ifdef TEST_CODE
    measureDistance = 10;
    if (testError == true){
      measureDistance = 2;
    }
  #endif
    if (measureDistance > HIGH_WATER_LEVEL){
      // GREEN
      //debugLog("Sonar Distance(cm: Green): ", sonarDistance, NULL, SCRN_OUT_SONAR);
      debugLog("Water Tank(cm: Green): ", measureDistance, NULL, SCRN_OUT_SONAR);
      retValue = SONAR_WITHIN_LIMIT_DISTANCE;
    } else if ((HIGH_WATER_LEVEL >= measureDistance) && (measureDistance > LOW_WATER_LEVEL))  {
      // YELLOW
      //debugLog("Sonar Distance(cm: Yellow): ", sonarDistance, NULL, SCRN_OUT_SONAR);
      debugLog("Water Tank(cm: Yellow): ", measureDistance, NULL, SCRN_OUT_SONAR);
      retValue = SONAR_WITHIN_LIMIT_DISTANCE;
    } else if (measureDistance <= LOW_WATER_LEVEL) {
      // Red
      //debugLog("Sonar Distance(cm: Red): ", sonarDistance, NULL, SCRN_OUT_SONAR);
      debugLog("Water Tank(cm: Red): ", measureDistance, NULL, SCRN_OUT_SONAR);
      retValue = SONAR_OVER_LIMIT_DISTANCE;
    }
  }
  return retValue;
}
