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
//Added sonar status
typedef enum{
   SONAR_NONE,
   SONAR_WITHIN_LIMIT_DISTANCE,
   SONAR_OVER_LIMIT_DISTANCE
}sonar_st;

void sonarSetup(void);
sonar_st sonar(void);

#ifdef __cplusplus
} // extern "C"
#endif
#endif /*_WATER_PUMP_H_*/
