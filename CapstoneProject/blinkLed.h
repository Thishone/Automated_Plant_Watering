#ifndef _BLINKLED_H_
#define _BLINKLED_H_
#ifdef __cplusplus
extern "C" {
#endif
#ifdef LED_FEATUR
void blinkLedSetup(void);
void blinkOnOff(void);
void ledOn(void);
void ledOff(void);
#endif
#ifdef __cplusplus
} // extern "C"
#endif
#endif /*_BLINKLED_H_*/
