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

// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;

// defines variables
long duration;
int sonarDistance = 0;
int old_sonarDistance = 0;


//1. If water level > 10cm, GREEN
//2. If 5 cm < water level > 10cm, YELLOW
//3. If water level < 5cm, RED and send message to refill water. Do not pump water if below 5cm.

//#define LIMIT_DISTANCE       15
#define FULL_WATER_LEVEL     20
#define HIGH_WATER_LEVEL     10
#define LOW_WATER_LEVEL      5
#define SPEED_SOUND 0.034

void sonarSetup(void)
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

int sonar(void)
{
  int retValue = SONAR_NONE;
  int measureDistance = 0;

  //debugLog("Running sonar", NONE_DATA, NULL, SCRN_OUTA);
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
  if (measureDistance > HIGH_WATER_LEVEL){
    // GREEN
#ifdef LED_FEATURE
    blinkYellowOff();
    blinkRedOff();
    blinkGreenOn();
#endif
    debugLog("Sonar Distance (Green): ", sonarDistance, NULL, SCRN_OUT_SONAR);
    retValue = SONAR_WITHIN_LIMIT_DISTANCE;
  } else if ((HIGH_WATER_LEVEL >= measureDistance) && (measureDistance > LOW_WATER_LEVEL))  {
    // YELLOW
#ifdef LED_FEATURE
    blinkGreenOff();
    blinkRedOff();
    blinkYellowOn();
#endif
    debugLog("Sonar Distance (Yellow): ", sonarDistance, NULL, SCRN_OUT_SONAR);
    retValue = SONAR_WITHIN_LIMIT_DISTANCE;
  } else if (measureDistance <= LOW_WATER_LEVEL) {
    // Red
#ifdef LED_FEATURE
    blinkGreenOff();
    blinkYellowOff();
    blinkRedOn();
#endif
    debugLog("Sonar Distance (Red): ", sonarDistance, NULL, SCRN_OUT_SONAR);
    retValue = SONAR_OVER_LIMIT_DISTANCE;
  }

//  if (sonarDistance > LIMIT_DISTANCE)
//  {
//    retValue = SONAR_OVER_LIMIT_DISTANCE;
//  } else {
//    retValue = SONAR_WITHIN_LIMIT_DISTANCE;
//  }
  
  // Prints the sonarDistance on the Serial Monitor
//  if (old_sonarDistance != sonarDistance){
//    debugLog("Sonar Distance: ", sonarDistance, NULL, SCRN_OUT_SONAR);
//    old_sonarDistance = sonarDistance;
//  }
    
  return retValue;
}
