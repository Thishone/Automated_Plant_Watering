#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_
#ifdef __cplusplus
extern "C" {
#endif
int bluetooth(void);
void bluetoothSerial(void);
void bluetoothSetup(void);

//Added Bluetooth status check
enum bt_status {
   BT_NONE,
   BT_AVAILABLE,
   BT_UNAVAILABLE
};
#ifdef __cplusplus
} // extern "C"
#endif
#endif /*_BLUETOOTH_H_*/
