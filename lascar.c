#include "lascar.h"

float get_temp(unsigned int t) {
    float rt = -200.0;

    for(; t>0; t--) {
        rt += STEPT;
    }

    return rt;
}

float get_hum(unsigned char h) {
    float rh = 0;

    for(; h>0x00; h--) {
        rh+= STEPH;
    }

    return rh;
}

hid_return
get_reading(HIDInterface* hid, char* packet, float* temp, float* hum) {
    hid_return ret;

    if((ret=read_device(hid, packet, HUMIDITY)) != HID_RET_SUCCESS) {
        fprintf(stderr, "Unable to read humidity (%d)\n", HUMIDITY);
        return ret;
    }

    *hum = get_hum((unsigned)packet[1]);

    if((ret=read_device(hid, packet, TEMPERATURE)) != HID_RET_SUCCESS) {
        fprintf(stderr, "Unable to read temperature (%d)\n", TEMPERATURE);
        return ret;
    }

    *temp = get_temp(pack((unsigned)packet[2], (unsigned)packet[1]));

    return ret;
}

HIDInterface* init_termo(HIDInterface* hid) {
    HIDInterfaceMatcher matcher = dev_id;
    hid_return i;

    i = hid_init();
    if(i != HID_RET_SUCCESS) {
        fprintf(stderr, "Could not init HID\n");
        hid = NULL;
    }

    hid = hid_new_HIDInterface();

    i = hid_force_open(hid, 0, &matcher, 3);
    if(i != HID_RET_SUCCESS) {
        fprintf(stderr, "Unable to open device\n");
        hid = NULL;
    }

    return hid;
}

hid_return restore_termo(HIDInterface* hid) {
    hid_return i;

    i = hid_close(hid);
    if(i != HID_RET_SUCCESS) {
        fprintf(stderr, "hid_close failed with return code %d\n", i);
    }

    hid_delete_HIDInterface(&hid);

    i = hid_cleanup();
    if(i != HID_RET_SUCCESS) {
        fprintf(stderr, "hid_cleanup failed with return code %d\n", i);
    }

    return i;
}

hid_return read_device(HIDInterface* hid, char* buf, int size) {
    hid_return i;

    i = hid_interrupt_read(hid, EP_HID_IN, buf, size, espera);
    if(i != HID_RET_SUCCESS) {
        fprintf(stderr, "hid_get_input_report failed with return code %d\n", i);
    }

    return i;
}

unsigned int pack(unsigned char a, unsigned char b) {
    unsigned int packed;

    packed = a;
    packed <<= 8;
    packed |= b;

    return packed;
}
