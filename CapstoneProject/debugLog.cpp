#include <Arduino.h>
#include "debugLog.h"

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
void debugLog(const char * string, int data, char *data_string, int mode)
{
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
#ifdef DEBUG_LOG
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
#endif
  }
  strcpy(string_log, string);
  data_log = data;
  strcpy(data_string_log, data_string);

}
