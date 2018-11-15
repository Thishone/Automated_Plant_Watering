// simple program to demo EzGUI
#include <Arduino.h>
#include <Servo.h>
#include "ezScrn.h"

const byte numChars = 90;
char receivedChars[numChars];
boolean newData = false;

int sliderValue;
int oldSliderValue;
char buttonValue[6];
char oldButtonValue[6];

const byte ledPin = 13;
const byte servoPin = 8;
Servo myServo;

byte servoPos = 0;
byte ledState = 0;

void ezScrnSetup(void) {
  
  //Serial.begin(115200);
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
  Serial.println("<+newScrn, size=40x30, tleft=0x0, bg=green, fg=black>");
    // add an area for text from the Arduino to be displayed
  Serial.println("<+tOut, name=outA, size=38x10, tleft=1x1, bg=yellow, fg=black>");
  
   // add an area for text from the slidA to be displayed
  Serial.println("<+tOut, name=outSlidA, size=16x2, tleft=2x12, bg=yellow, fg=black>");
    // add a slider to control a servo
  Serial.println("<+slid, name=slidA, size=15x1, tleft=22x12, range=0x100x50x5>");

   // add an area for text from the slidA to be displayed
  Serial.println("<+tOut, name=outSlidB, size=16x2, tleft=2x15, bg=yellow, fg=black>");
    // add a slider to control a servo
  Serial.println("<+slid, name=slidB, size=15x1, tleft=22x15, range=0x100x50x5>"); //(min, max, position, step)

   // add an area for text from the moisture to be displayed
  Serial.println("<+tOut, name=outMoisture, size=16x2, tleft=2x20, bg=yellow, fg=black>");

   // add an area for text from the tempture to be displayed
  Serial.println("<+tOut, name=outTemp, size=16x2, tleft=2x23, bg=yellow, fg=black>");

  // add an area for text from the light to be displayed
  Serial.println("<+tOut, name=outLight, size=16x2, tleft=2x26, bg=yellow, fg=black>");
  
    // add a QUIT button
  Serial.println("<+quit, name=Quit, size=8x2, tleft=30x25, bg=red, fg=black>");
    // terminate the design
    
  Serial.println("<+endScrn>");

  myServo.attach(servoPin);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
}



void updateLED() {
  if (strcmp(buttonValue, "ledA") == 0) {
    ledState = ! ledState;
    digitalWrite(ledPin, ledState);
  }
}

void moveServo() {
  if (sliderValue != oldSliderValue) {
    myServo.write(sliderValue);
  }
}

void replyToEzGUI(void) {
    
      // replace the text in textBox outB
    Serial.print("<-outB, ");
    Serial.print("Slider Position ");
    Serial.print(sliderValue);
    Serial.print(">");
  }



void recvWithStartEndMarkers() {
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

void parseData() {

    // split the data into its parts
    // this must be tailored to the expected data from the EzGUI
    // in this demo the data will be sliderValue and buttonValue, in that order
  
    // save the existing values in case they are needed for comparison
  oldSliderValue = sliderValue;
  strcpy(oldButtonValue, buttonValue);
    
  char * strtokIndx; // this is used by strtok() as an index
  
  strtokIndx = strtok(receivedChars,","); // find the first part
  sliderValue = atoi(strtokIndx);
  
  strtokIndx = strtok(NULL, ",");  // find the next part
  strcpy(buttonValue, strtokIndx);

}

void ezScrn(void) {
  recvWithStartEndMarkers();
  if (newData == true) {
    parseData();
    moveServo();
    replyToEzGUI();
    newData = false;
  }
}
