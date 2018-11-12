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
extern void debugLog(const char * string, int data, char * data_string, int mode);

#ifdef __cplusplus
} // extern "C"
#endif
#endif /*_DEBUG_LOG_*/
