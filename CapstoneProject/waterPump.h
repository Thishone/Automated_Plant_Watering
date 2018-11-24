/*
 * waterPump.h
 *
 *  Created on: Nov 15, 2018
 *      Author: Jin Taek Lee, Thishone Wijayakumar, Ajo Cherian Thomas
 */
#ifndef _WATER_PUMP_H_
#define _WATER_PUMP_H_
#ifdef __cplusplus
extern "C" {
#endif
void waterPumpSetup(void);
int waterPumpOn(void);
int waterPumpOff(void);
int alertWaterIsLow(void);

//Added Water Pump status
typedef  enum{
   PUMP_NONE,
   PUMP_ON,
   PUMP_OFF
}waterPump_st;


#ifdef __cplusplus
} // extern "C"
#endif
#endif /*_WATER_PUMP_H_*/
