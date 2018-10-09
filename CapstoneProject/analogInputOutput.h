#ifndef _ANALOG_INPUT_OUTPUT_
#define _ANALOG_INPUT_OUTPUT_
#ifdef __cplusplus
extern "C" {
#endif

// Soil Humidity Sensor
extern int analogReadHumidityValue;
void analogReadHumidity(void);
void analogWriteHumidity(void);

// Temperature Sensor
extern int analogReadTemperatureValue;
void analogReadTemperature(void);
void analogWriteTemperature(void);

// Light Sensor 
extern int analogReadLightValue;
void analogReadLight(void);
void analogWriteLight(void);

#ifdef __cplusplus
} // extern "C"
#endif
#endif /*_ANALOG_INPUT_OUTPUT_*/
