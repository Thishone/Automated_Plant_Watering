/*
 * sonar.h
 *
 *  Created on: Nov 15, 2018
 *      Author: Jin Taek Lee, Thishone Wijayakumar, Ajo Cherian Thomas
 */
#ifndef _SONAR_H_
#define _SONAR_H_
#ifdef __cplusplus
extern "C" {
#endif
void sonarSetup(void);
int sonar(void);

//Added sonar status
enum sonar_status {
   SONAR_NONE,
   SONAR_WITHIN_LIMIT_DISTANCE,
   SONAR_OVER_LIMIT_DISTANCE
};

#ifdef __cplusplus
} // extern "C"
#endif
#endif /*_WATER_PUMP_H_*/
