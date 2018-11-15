#include <Arduino.h>
#include "sonar.h"
#include "debugLog.h"

// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;

// defines variables
long duration;
int sonarDistance = 0;
int pre_sonarDistance = 0;

#define LIMIT_DISTANCE  15
#define SPEED_SOUND 0.034

void sonarSetup(void)
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

int sonar(void)
{
  int retValue = SONAR_NONE;

  //debugLog("Running sonar", NONE_DATA, NULL, DEBUG_DEV);
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
  sonarDistance= duration*SPEED_SOUND/2;

  if (sonarDistance > LIMIT_DISTANCE)
  {
    retValue = SONAR_OVER_LIMIT_DISTANCE;
  } else {
    retValue = SONAR_WITHIN_LIMIT_DISTANCE;
  }
  
  // Prints the sonarDistance on the Serial Monitor
  if (pre_sonarDistance != sonarDistance){
    debugLog("Sonar sonarDistance: ", sonarDistance, NULL, DEBUG_DEV, SCRN_OUTA);
  }
  
  
  return retValue;
}
