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

//for testing
extern float soilMoisturePercentage;
extern float old_soilMoisturePercentage;

#ifdef TEST_CODE
extern boolean testError;
#endif

extern boolean learningPotSize;
extern boolean normalWatering;

const byte numChars = 30;
char receivedChars[numChars];
boolean newData = false;

char buttonValue[10];

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
  int k;    // counter variable
  char myChar;

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

  Serial.println(F("<Arduino is ready>"));
    // initiate the screen design
  Serial.println(F("<+newScrn, size=40x44, tleft=0x0, bg=green, fg=black>"));
    // add an area for text from the Arduino to be displayed
  Serial.println(F("<+tOut, name=outA, size=38x14, tleft=1x1, bg=yellow, fg=black>"));
  
   // add an area for text from the slidA to be displayed
  Serial.println(F("<+tOut, name=outSlidMax, size=16x2, tleft=2x16, bg=yellow, fg=black>"));
    // add a slider to control a servo
  Serial.println(F("<+slid, name=slidMax, size=15x1, tleft=22x16, range=0x100x0x5>"));

   // add an area for text from the slidA to be displayed
  Serial.println(F("<+tOut, name=outSlidMin, size=16x2, tleft=2x19, bg=yellow, fg=black>"));
    // add a slider to control a servo
  Serial.println(F("<+slid, name=slidMin, size=15x1, tleft=22x19, range=0x100x0x5>")); //(min, max, position, step)

   // add an area for text from the moisture to be displayed
  Serial.println(F("<+tOut, name=outMoisture, size=16x2, tleft=2x24, bg=yellow, fg=black>"));

    // add a button that will operate an Learning
  Serial.println(F("<+btn, name=Learning, size=11x2, tleft=24x24, bg=black, fg=orange>"));

   // add an area for text from the Watering Time to be displayed
  Serial.println(F("<+tOut, name=outWateringTime, size=16x2, tleft=22x27, bg=yellow, fg=black>"));

    // add a button that will operate an Learning
  Serial.println(F("<+btn, name=Normal, size=11x2, tleft=24x30, bg=black, fg=orange>"));

   // add an area for text from the Humidity to be displayed
  Serial.println(F("<+tOut, name=outHumidity, size=16x2, tleft=2x27, bg=yellow, fg=black>"));

   // add an area for text from the tempture to be displayed
  Serial.println(F("<+tOut, name=outTemp, size=16x2, tleft=2x30, bg=yellow, fg=black>"));

  // add an area for text from the light to be displayed
  Serial.println(F("<+tOut, name=outLight, size=16x2, tleft=2x33, bg=yellow, fg=black>"));
#ifdef TEST_CODE
    // add a button that will operate an Learning
  Serial.println(F("<+btn, name=Test, size=11x2, tleft=24x33, bg=black, fg=orange>"));
#endif 
  // add an area for text from the sonar distace to be displayed
  Serial.println(F("<+tOut, name=outOverflow, size=24x2, tleft=2x36, bg=yellow, fg=black>"));

  // add an area for text from the sonar distace to be displayed
  Serial.println(F("<+tOut, name=outSonar, size=24x2, tleft=2x39, bg=yellow, fg=black>"));
  
    // add a QUIT button
  Serial.println(F("<+quit, name=Quit, size=8x2, tleft=30x39, bg=red, fg=black>"));
    // terminate the design
    
  Serial.println(F("<+endScrn>"));

  myServo.attach(servoPin);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
  replyToEzGUI();
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : updateButton()
// DESCRIPTION   : 
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void updateButton() {
  if (strcmp(buttonValue, "Learning") == 0) {
    learningPotSize = !learningPotSize;
  } else if (strcmp(buttonValue, "Normal") == 0){
    normalWatering =!normalWatering;
  } 
#ifdef TEST_CODE
  else if (strcmp(buttonValue, "Test") == 0){
    testError =!testError;
  }
#endif
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : moveServo()
// DESCRIPTION   : 
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void moveServo(void) {
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
  //for testing
#ifdef TEST_CODE
  soilMoisturePercentage = sliderMaxValue;
#endif
  setMaxMoistureValue(sliderMaxValue);
  Serial.print(">");

  Serial.print("<-outSlidMin, ");
  Serial.print("Moisture Min Value: ");
  Serial.print(sliderMinValue);

  //for testing
#ifdef TEST_CODE
  old_soilMoisturePercentage = sliderMinValue;
#endif
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
  strcpy(buttonValue, strtokIndx);

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
    updateButton();
    moveServo();
    replyToEzGUI();
    newData = false;
  }
}
