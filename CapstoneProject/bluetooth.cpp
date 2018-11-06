#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wstring.h>
#include "blinkLed.h"
#include "bluetooth.h"
#include "waterPump.h"
#include "analogInputOutput.h"

#define BTserialRX 5
#define BTserialTX 6
#define RX 0
#define TX 1

#define MAX_MOISTURE "max"
#define MIN_MOISTURE "min"

SoftwareSerial BTserial(BTserialRX,BTserialTX);
         
String readData = ""; //Variable for storing received data
String BTserial_readData = ""; //Variable for storing received data


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
  if(Serial.available() > 0)      // Send data only when you receive data:
  {
    while(Serial.available()){
      readData += (char)Serial.read();        //Read the incoming data & store into data
      delay(500);
    }
    Serial.print("Bluetooth incoming data:");
    Serial.println(readData);          //Print Value inside data in Serial monitor
    Serial.print("\n");
       
    if(readData == "on")              // Checks whether value of data is equal to 1
    {
      retValue |= BT_READ_ON;
    }
    else if(readData == "off")         //  Checks whether value of data is equal to 0
    {
      retValue |= BT_READ_OFF;
    }

    readData = "";
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
    Serial.print("bluetoothSerial incoming data:");
    BTserial_readData = (char)BTserial.read();
    Serial.print(BTserial_readData);

    max_moisture = 60;
    min_moisture = 30;
   
    BTserial_readData = "";
  }
}
