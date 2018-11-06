#include <Arduino.h>
#include "sonar.h"

// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;

// defines variables
long duration;
int distance;

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

  Serial.println("Running sonar");
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance= duration*SPEED_SOUND/2;

  if (distance > LIMIT_DISTANCE)
  {
    retValue = SONAR_OVER_LIMIT_DISTANCE;
  } else {
    retValue = SONAR_WITHIN_LIMIT_DISTANCE;
  }
  
  // Prints the distance on the Serial Monitor
  Serial.print("Sonar Distance: ");
  Serial.println(distance);                   // wait for a second
//  Serial.println("\n");
  
  return retValue;
}
