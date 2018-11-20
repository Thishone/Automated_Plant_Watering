/*
 * ezScrn.h
 *
 *  Created on: Nov 15, 2018
 *      Author: Jin Taek Lee, Thishone Wijayakumar, Ajo Cherian Thomas
 */
#ifndef _EZSCRN_H_
#define _EZSCRN_H_
#ifdef __cplusplus
extern "C" {
#endif
void ezScrnSetup(void);
void ezScrn(void);
void replyToEzGUI(void);

void recvWithStartEndMarkers(void);

extern boolean ezScrn_on;
extern boolean newData;

#ifdef __cplusplus
} // extern "C"
#endif
#endif /*_EZSCRN_H_*/
