#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wstring.h>
#include "blinkLed.h"
#include "bluetooth.h"

#define BTserialRX 5
#define BTserialTX 6
#define RX 0
#define TX 1

SoftwareSerial BTserial(BTserialRX,BTserialTX);
//char incomingData = 0;            //Variable for storing received data
String incomingData = ""; 
int avail = 0;
String Temperature = "Temperature";
String PercentageHumidity = "PercentageHumidity";
String MeasuredLux = "MeasuredLux";


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
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void bluetooth(void)
{
  Serial.println("Bluetooth:");
  if(Serial.available() > 0)      // Send data only when you receive data:
  {
    while(Serial.available()){
      incomingData += (char)Serial.read();        //Read the incoming data & store into data
    }
    Serial.println("Bluetooth incoming data:");
    Serial.println(incomingData);          //Print Value inside data in Serial monitor
    Serial.print("\n");        
    if(incomingData == "on")              // Checks whether value of data is equal to 1
      ledOn();   //If value is 1 then LED turns ON
    else if(incomingData == "off")         //  Checks whether value of data is equal to 0
      ledOff();    //If value is 0 then LED turns OFF

    incomingData = "";
    delay(500);
  }
}

/////////////////////////////////////////////////////////////////
// FUNCTION      : bluetooth()
// DESCRIPTION   : This function can set bluetooth serial pin
// PARAMETERS   :   
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void bluetoothSerial(void)
{
  Serial.println("bluetoothSerial:");
  BTserial.begin(9600);
  BTserial.print("AT");
  if(BTserial.available() > 0)
  {
    char aChar = BTserial.read();
    Serial.print(aChar);
  }
  delay(500);
}
