/*
 * debugLog.cpp
 *
 *  Created on: Nov 15, 2018
 *      Author: Jin Taek Lee, Thishone Wijayakumar, Ajo Cherian Thomas
 */
#include <Arduino.h>
#include "debugLog.h"
#include "ezScrn.h"

//#define LOG_DATA_SIZE 20
//char string_log[LOG_DATA_SIZE] = {0,};
//int data_log = 0;
//char data_string_log[10] = {0,};

/////////////////////////////////////////////////////////////////
// FUNCTION      : debugLog()
// DESCRIPTION   : This function use for debug
// PARAMETERS   :
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void debugLog(const char * string, int data, char *data_string, int scrn_ind)
{
  static int addLine = 0;
#ifdef DEBUG_LOG
  if (scrn_ind == SCRN_OUTA){
    if (addLine < 5){
      Serial.print("<+outA, ");
      addLine ++;
    } else {
      addLine = 0;
      Serial.print("<-outA, ");
    }

  } else if (scrn_ind == SCRN_OUT_SLID_MAX){
    Serial.print("<-outSlidMax, ");
  } else if (scrn_ind == SCRN_OUT_SLID_MIN){
    Serial.print("<-outSlidMin, ");    
  } else if (scrn_ind == SCRN_OUT_MOISTURE){
    Serial.print("<-outMoisture, ");    
  } else if (scrn_ind == SCRN_OUT_TEMPERATURE){
    Serial.print("<-outTemp, ");    
  } else if (scrn_ind == SCRN_OUT_LIGHT){
    Serial.print("<-outLight, ");    
  } else if (scrn_ind == SCRN_OUT_SONAR){
    Serial.print("<-outSonar, ");    
  }

  if (data != NONE_DATA) {
    Serial.print(string);
    Serial.println(data);
  } else {
    if (data_string != NULL) {
      Serial.print(string);
      Serial.println(data_string);
    } else {
      Serial.println(string);
    }
  }

  Serial.print(">");
  if (newData == true) {
    replyToEzGUI();
    newData = false;
  }  

//  strcpy(string_log, string);
//  data_log = data;
//  strcpy(data_string_log, data_string);
#endif

}
