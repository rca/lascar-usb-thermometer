#ifndef __LASCAR_H__
#define __LASCAR_H__ 1

#include <hid.h>

#define EP_HID_IN 0x81
#define espera 520 /* wait timeout */
#define STEPT 0.1
#define STEPH 0.5
#define dev_id { 0x1781, 0x0ec4, NULL, NULL, 0 }

#define HUMIDITY 2
#define TEMPERATURE 3

/* it's likely the following three functions are the most useful */

/**
 * Open the HID interface
 */
HIDInterface* init_termo(HIDInterface*);

/**
 * Close the HID interface
 */
hid_return restore_termo(HIDInterface*);

/*
 * Retrieve temperature and humidity readings from the device
 */
hid_return
get_reading(HIDInterface* hid,
            char* packet, float* temp, float* hum, int get_f);

/* the following functions are useful if only temp or humidity is desired */

/**
 * Return the temperature
 *
 * The second parameter can be 0 for Celcius or 1 for Farenheit
 */
float get_temp(unsigned int, int);

/**
 * Return the humidity as a percentage
 */
float get_hum(unsigned char);

/* the following functions are used internally and should not be needed */

/*
 * The retry parameter can be used to tell get_reading() to
 * automatically retry on error.
 */
hid_return
get_reading_r(HIDInterface* hid,
              char* packet, float* temp, float* hum, int get_f, int retries);

/**
 * Read the specified number of bytes from the device
 */
hid_return read_device(HIDInterface*, char*, int);

/**
 * Pack two chars into an int
 */
unsigned int pack(unsigned char, unsigned char);

#endif /* __LASCAR_H__ */
