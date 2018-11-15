#ifndef _DEBUG_LOG_
#define _DEBUG_LOG_
#ifdef __cplusplus
extern "C" {
#endif

#define DEBUG_LOG
#define NONE_DATA -100

enum debug_mode {
   DEBUG_DEV,
   DEBUG_RELEASE,
};

enum scrn_ind {
   SCRN_NONE,
   SCRN_OUTA,
   SCRN_OUT_SLIDA,
   SCRN_SLIDA,
   SCRN_OUT_SLIDB,
   SCRN_SLIDB,
   SCRN_OUT_MOISTURE,
   SCRN_OUT_TEMPERATURE,
   SCRN_OUT_LIGHT
};

extern void debugLog(const char * string, int data, char * data_string, int mode, int scrn_ind);

#ifdef __cplusplus
} // extern "C"
#endif
#endif /*_DEBUG_LOG_*/
