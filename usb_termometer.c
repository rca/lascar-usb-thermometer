/*  Copyright (c) 2010 Ángel Sancho angel.sancho@gmail.com
 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/> 
    									**/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/* human interface device API */
#include <hid.h>

/* lascar API */
#include "lascar.h"




if((hid=init_termo(hid))==NULL){
	fprintf(stderr,"Device NOT present.\n");
	exit (-1);
}

ret = read_device(hid,packet,2);
	if (ret != HID_RET_SUCCESS) {
		fprintf(stderr,"read_device failed with return code %d\n",ret);
		ret = restore_termo(hid);
		if (ret != HID_RET_SUCCESS) {
			fprintf(stderr,"restore_termo failed with return code %d\n",ret);
			exit(-1);
		}
		hid=init_termo(hid);
	}
printf("Hum. : %.1f\n",get_hum((unsigned)packet[1]));
ret = read_device(hid,packet,3);
if (ret != HID_RET_SUCCESS) {
                fprintf(stderr,"read_device failed with return code %d\n",ret);
                ret = restore_termo(hid);
                if (ret != HID_RET_SUCCESS) {
                        fprintf(stderr,"restore_termo failed with return code %d\n",ret);
                        exit(-1);
                }
                hid=init_termo(hid);
        }
ret = restore_termo(hid);
printf("Temp.: %.1f\n",get_temp(pack((unsigned)packet[2],(unsigned)packet[1])));
return 0;
}


}



}
