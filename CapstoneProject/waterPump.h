#ifndef _WATER_PUMP_H_
#define _WATER_PUMP_H_
#ifdef __cplusplus
extern "C" {
#endif
void waterPumpSetup(void);
int waterPumpOn(void);
int waterPumpOff(void);

//Added Water Pump status
enum waterPump_status {
   PUMP_NONE,
   PUMP_ON,
   PUMP_OFF
};

#ifdef __cplusplus
} // extern "C"
#endif
#endif /*_WATER_PUMP_H_*/
