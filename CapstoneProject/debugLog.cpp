#include <Arduino.h>
#include "debugLog.h"
#include "ezScrn.h"

#define LOG_DATA_SIZE 50
char string_log[LOG_DATA_SIZE] = {0,};
int data_log = 0;
char data_string_log[10] = {0,};

/////////////////////////////////////////////////////////////////
// FUNCTION      : debugLog()
// DESCRIPTION   : This function use for debug
// PARAMETERS   :
// RETURNS       : none
/////////////////////////////////////////////////////////////////
void debugLog(const char * string, int data, char *data_string, int mode, int scrn_ind)
{
#ifdef DEBUG_LOG
  if (scrn_ind == SCRN_OUTA){
    Serial.print("<+outA, ");
  } else if (scrn_ind == SCRN_OUT_SLIDA){
    Serial.print("<-outSlidA, ");
  } else if (scrn_ind == SCRN_OUT_SLIDB){
    Serial.print("<-outSlidB, ");    
  } else if (scrn_ind == SCRN_OUT_MOISTURE){
    Serial.print("<-outMoisture, ");    
  } else if (scrn_ind == SCRN_OUT_TEMPERATURE){
    Serial.print("<-outTemp, ");    
  } else if (scrn_ind == SCRN_OUT_LIGHT){
    Serial.print("<-outLight, ");    
  }

  if (mode == DEBUG_RELEASE)
  {
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
  }
  else if (mode == DEBUG_DEV)
  {
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
  }
  Serial.print(">");
  replyToEzGUI();
  strcpy(string_log, string);
  data_log = data;
  strcpy(data_string_log, data_string);
#endif

}
