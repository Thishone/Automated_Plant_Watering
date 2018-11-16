#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_
#ifdef __cplusplus
extern "C" {
#endif
#ifdef BLUETOOTH_FEATU
int bluetooth(void);
void bluetoothSerial(void);
void bluetoothSetup(void);

//Added Bluetooth status check
enum bt_status {
   BT_NONE = 0x00,
   BT_AVAILABLE = 0x01,
   BT_READ_ON = 0x02,
   BT_READ_OFF = 0x04,
   BT_UNAVAILABLE = 0x08,
};
#endif
#ifdef __cplusplus
} // extern "C"
#endif
#endif /*_BLUETOOTH_H_*/
