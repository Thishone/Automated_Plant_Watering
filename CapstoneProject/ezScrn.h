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

#ifdef __cplusplus
} // extern "C"
#endif
#endif /*_EZSCRN_H_*/
