#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_
#ifdef __cplusplus
extern "C" {
#endif
int bluetooth(void);
void bluetoothSerial(void);
void bluetoothSetup(void);

#define BTserialRX 5
#define BTserialTX 6

//Added Bluetooth status check
enum bt_status {
   BT_NONE = 0x00,
   BT_AVAILABLE = 0x01,
   BT_READ_ON = 0x02,
   BT_READ_OFF = 0x04,
   BT_UNAVAILABLE = 0x08,
};
#ifdef __cplusplus
} // extern "C"
#endif
#endif /*_BLUETOOTH_H_*/
