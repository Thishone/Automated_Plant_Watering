#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wstring.h>
#include "blinkLed.h"
#include "bluetooth.h"
#include "waterPump.h"
#include "analogInputOutput.h"
#include "debugLog.h"
#include "ezScrn.h"

//#define BTserialRX 5
//#define BTserialTX 6
#define RX 0
#define TX 1

#define MAX_MOISTURE "max"
#define MIN_MOISTURE "min"

SoftwareSerial BTserial(BTserialRX,BTserialTX);

#define READ_DATA_SIZE 10
char readData[READ_DATA_SIZE] = {0,}; //Variable for storing received data
char BTserial_readData[READ_DATA_SIZE] = {0,}; //Variable for storing received data


/////////////////////////////////////////////////////////////////
// FUNCTION      : bluetoothSetup()
// DESCRIPTION   : This function sets pin
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void bluetoothSetup(void)
{
  pinMode(RX,INPUT);
  pinMode(TX,OUTPUT);
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : bluetooth()
// DESCRIPTION   : This function use default RX(D0) and TX(D1) on the arduino
// PARAMETERS   :   
// RETURNS       : Bluetooth status
//                 BT_NONE
//                 BT_AVAILABLE
/////////////////////////////////////////////////////////////////
int bluetooth(void)
{
  int retValue = BT_NONE;
  const char* delim = " ";
  char * token;
  char * tempStr;
  byte size = 0;
  
  if(Serial.available() > 0)      // Send data only when you receive data:
  {
    while(Serial.available()){
      size = Serial.readBytes(readData, READ_DATA_SIZE); //Read the incoming data & store into data
      readData[size] =' ';
      delay(500);
    }
    debugLog("Bluetooth incoming data: ", NONE_DATA, readData, DEBUG_DEV, SCRN_OUTA);
    
    token = strtok(readData, delim);

    debugLog("token: ", NONE_DATA, token, DEBUG_DEV, SCRN_OUTA);
    
    if (strcmp(MAX_MOISTURE, token) == 0)
    {
      tempStr = strtok(NULL, delim);
      debugLog("MAX tempStr: ", NONE_DATA, tempStr, DEBUG_DEV, SCRN_OUTA);
      max_moisture = atoi(tempStr);
    } 
    else if (strcmp(MIN_MOISTURE, token) == 0)
    {
      tempStr = strtok(NULL, delim);
      debugLog("MIN tempStr: ", NONE_DATA, tempStr, DEBUG_DEV, SCRN_OUTA);
      min_moisture = atoi(tempStr);
    }
    else if (strcmp("ez", token) == 0){
      tempStr = strtok(NULL, delim);
      debugLog("MIN tempStr: ", NONE_DATA, tempStr, DEBUG_DEV, SCRN_OUTA);
      ezScrn_on = atoi(tempStr);
    }
    if (strcmp(readData, "on") == 0)   // Checks whether value of data is equal to 1
    {
      retValue |= BT_READ_ON;  
      //debugLog("BT_READ_ON: ", retValue, NULL, DEBUG_DEV); 
    }     
    else if (strcmp(readData, "off") == 0)   //  Checks whether value of data is equal to 0
    {
      retValue |= BT_READ_OFF;   
      //debugLog("BT_READ_OFF: ", retValue, NULL,DEBUG_DEV);  
    }

    memset(readData, '0', sizeof(readData));

    retValue |= BT_AVAILABLE;
  } else {
    retValue |= BT_UNAVAILABLE;
  }

  return retValue;
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : bluetooth()
// DESCRIPTION   : This function can set bluetooth serial pin
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void bluetoothSerial(void)
{  
  BTserial.begin(9600);
  BTserial.print("AT");
  if(BTserial.available() > 0)
  {
    //BTserial_readData = (char)BTserial.read();
    Serial.readBytes(BTserial_readData, READ_DATA_SIZE);

    debugLog("bluetoothSerial incoming data: ", NONE_DATA, BTserial_readData, DEBUG_DEV, SCRN_OUTA);  
   
    memset(BTserial_readData, '0', sizeof(readData));
  }
}
