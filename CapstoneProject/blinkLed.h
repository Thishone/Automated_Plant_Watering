/*
 * blinkLed.h
 *
 *  Created on: Nov 15, 2018
 *      Author: Jin Taek Lee, Thishone Wijayakumar, Ajo Cherian Thomas
 */
#ifndef _BLINKLED_H_
#define _BLINKLED_H_
#ifdef __cplusplus
extern "C" {
#endif
//#define LED_FEATUR
#ifdef LED_FEATUR
void blinkLedSetup(void);
void blinkOnOff(void);
void ledOn(void);
void ledOff(void);

void blinkGreenOn(void);
void blinkGreenOff(void);
void blinkYellowOn(void);
void blinkYellowOff(void);
void blinkRedOn(void);
void blinkRedOff(void);

#endif
#ifdef __cplusplus
} // extern "C"
#endif
#endif /*_BLINKLED_H_*/
