/**
 * Copyright (c) 2010 Ángel Sancho angel.sancho@gmail.com
 * Improvements by Roberto Aguilar roberto.c.aguilar@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/* human interface device API */
#include <hid.h>

/* lascar API */
#include "lascar.h"

#define MAX_ERRORS 10
#define SLEEP_TIME 1.0

int main()
{
    char packet[] = {0x00, 0x00, 0x00};
    HIDInterface* hid = NULL;
    hid_return ret;

    float temp, hum;

    int status = 0;
    int error_count = 0;

    int get_f = 1;

    if((hid=init_termo(hid)) == NULL) {
        fprintf(stderr, "Device NOT present.\n");
        exit(-1);
    }

    while(1) {
        status = 0;

        ret = get_reading(hid, packet, &temp, &hum, get_f);
        if(ret != HID_RET_SUCCESS) {
            status = -1;
        }

        if(status == 0) {
            printf("temp: %.1f, hum: %.1f\n", temp, hum);

            /* reset the error count on successful read */
            error_count = 0;
        } else if(error_count > MAX_ERRORS) {
            fprintf(stderr, "Too many errors to continue\n");
            exit(-1);
        } else {
            error_count += 1;
        }

        sleep(SLEEP_TIME);
    }

    ret = restore_termo(hid);

    return 0;
}
