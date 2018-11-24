/*
 * ezScrn.cpp
 *
 *  Created on: Nov 15, 2018
 *      Author: Jin Taek Lee, Thishone Wijayakumar, Ajo Cherian Thomas
 */
#include <Arduino.h>
#include <Servo.h>
#include "ezScrn.h"
#include "debugLog.h"
#include "sensors.h"

const byte numChars = 50;
char receivedChars[numChars];
boolean newData = false;

int sliderMaxValue = 0;
int oldSliderMaxValue = 0;

int sliderMinValue = 0;
int oldSliderMinValue = 0;

const byte ledPin = 13;
const byte servoPin = 8;
Servo myServo;

byte servoPos = 0;
byte ledState = 0;

/////////////////////////////////////////////////////////////////
// FUNCTION      : ezScrnSetup()
// DESCRIPTION   : This function setup the screen
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void ezScrnSetup(void) 
{
  // wait for python to send <Python ready>
  boolean startReceived = false;
  while (startReceived == false) {
    newData = false;
    recvWithStartEndMarkers();
    if (newData == true) {
      if (strcmp(receivedChars, "Python ready") == 0) {
        startReceived = true;
      }
    }
  }
		// send acknowledgment

  Serial.println("<Arduino is ready>");
    // initiate the screen design
  Serial.println("<+newScrn, size=40x34, tleft=0x0, bg=green, fg=black>");
    // add an area for text from the Arduino to be displayed
  Serial.println("<+tOut, name=outA, size=38x10, tleft=1x1, bg=yellow, fg=black>");
  
   // add an area for text from the slidA to be displayed
  Serial.println("<+tOut, name=outSlidMax, size=16x2, tleft=2x12, bg=yellow, fg=black>");
    // add a slider to control a servo
  Serial.println("<+slid, name=slidMax, size=15x1, tleft=22x12, range=0x100x0x5>");

   // add an area for text from the slidA to be displayed
  Serial.println("<+tOut, name=outSlidMin, size=16x2, tleft=2x15, bg=yellow, fg=black>");
    // add a slider to control a servo
  Serial.println("<+slid, name=slidMin, size=15x1, tleft=22x15, range=0x100x0x5>"); //(min, max, position, step)

   // add an area for text from the moisture to be displayed
  Serial.println("<+tOut, name=outMoisture, size=16x2, tleft=2x20, bg=yellow, fg=black>");

   // add an area for text from the tempture to be displayed
  Serial.println("<+tOut, name=outTemp, size=16x2, tleft=2x23, bg=yellow, fg=black>");

   // add an area for text from the Humidity to be displayed
  Serial.println("<+tOut, name=outHumidity, size=16x2, tleft=2x26, bg=yellow, fg=black>");
  
  // add an area for text from the light to be displayed
  Serial.println("<+tOut, name=outLight, size=16x2, tleft=2x29, bg=yellow, fg=black>");

  // add an area for text from the sonar distace to be displayed
  Serial.println("<+tOut, name=outSonar, size=24x2, tleft=2x32, bg=yellow, fg=black>");
  
    // add a QUIT button
  Serial.println("<+quit, name=Quit, size=8x2, tleft=30x30, bg=red, fg=black>");
    // terminate the design
    
  Serial.println("<+endScrn>");

  myServo.attach(servoPin);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
  replyToEzGUI();
}


/////////////////////////////////////////////////////////////////
// FUNCTION      : moveServo()
// DESCRIPTION   : 
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void moveServo() {
  if (sliderMaxValue != oldSliderMaxValue) {
    myServo.write(sliderMaxValue);
  }

  if (sliderMinValue != oldSliderMinValue) {
    myServo.write(sliderMinValue);
  }
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : replyToEzGUI()
// DESCRIPTION   : 
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void replyToEzGUI(void) 
{
    // replace the text in textBox outB
  Serial.print("<-outSlidMax, ");
  Serial.print("Moisture Max Value: ");
  Serial.print(sliderMaxValue);
  setMaxMoistureValue(sliderMaxValue);
  Serial.print(">");

  Serial.print("<-outSlidMin, ");
  Serial.print("Moisture Min Value: ");
  Serial.print(sliderMinValue);
  setMinMoistureValue(sliderMinValue);
  Serial.print(">");    
}


/////////////////////////////////////////////////////////////////
// FUNCTION      : recvWithStartEndMarkers()
// DESCRIPTION   : 
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void recvWithStartEndMarkers() 
{
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;
  
  if (Serial.available() > 0) {
    while (Serial.available() > 0 && newData == false) { 
      rc = Serial.read();
      
      if (recvInProgress == true) {
        if (rc != endMarker) {
          receivedChars[ndx] = rc;
          ndx++;
          if (ndx >= numChars) {
            ndx = numChars - 1;
          }
        }
        else {
          receivedChars[ndx] = '\0'; // terminate the string
          recvInProgress = false;
          ndx = 0;
          newData = true;
        }
      }
      else if (rc == startMarker) {
        recvInProgress = true;
      }
    }
  }
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : parseData()
// DESCRIPTION   : 
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void parseData() {

    // split the data into its parts
    // this must be tailored to the expected data from the EzGUI
    // in this demo the data will be sliderValue and buttonValue, in that order
  
    // save the existing values in case they are needed for comparison
  oldSliderMaxValue = sliderMaxValue;
  oldSliderMinValue = sliderMinValue;
  //strcpy(oldButtonValue, buttonValue);
    
  char * strtokIndx; // this is used by strtok() as an index

  strtokIndx = strtok(receivedChars,","); // find the first part
  sliderMaxValue = atoi(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  sliderMinValue = atoi(strtokIndx);
  
  strtokIndx = strtok(NULL, ",");  // find the next part
  //strcpy(buttonValue, strtokIndx);

}

/////////////////////////////////////////////////////////////////
// FUNCTION      : parseData()
// DESCRIPTION   : 
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void ezScrn(void) {
  recvWithStartEndMarkers();
  if (newData == true) {
    parseData();
    moveServo();
    replyToEzGUI();
    newData = false;
  }
}
