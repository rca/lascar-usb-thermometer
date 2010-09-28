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
    									*/

#include <hid.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#define EP_HID_IN             0x81
#define espera		      400
#define STEPT 0.1
#define STEPH 0.5
#define dev_id { 0x1781, 0x0ec4, NULL, NULL, 0 }

/* functions */
HIDInterface* init_termo(HIDInterface*);
hid_return restore_termo(HIDInterface*);
hid_return read_device(HIDInterface*,char*,int);
void print_packet(char*,int);
unsigned int pack(unsigned char, unsigned char);
float get_temp(unsigned int);
float get_hum(unsigned char);
/* functions */

int main(){
/* vars */

unsigned int ptemperatura;
char packet[]={0x00,0x00,0x00};
HIDInterface* hid=NULL;
hid_return ret;



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
printf("Hum. : %.1f\n",get_hum(packet[1]));
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
ptemperatura=pack((unsigned)packet[2],(unsigned)packet[1]);
printf("Temp.: %.1f\n",get_temp(ptemperatura));
return 0;
}

float get_temp(unsigned int t){
	float rt=-200.0;
	for (;t>0;t--){
		rt+=STEPT;
	}
	return rt;
}
float get_hum(unsigned char h){
	float rh=0;
	for (;h>0x00;h--){
		rh+=STEPH;
	}
	return rh;
}
HIDInterface* init_termo(HIDInterface* hid){
 	HIDInterfaceMatcher matcher =  dev_id;
	hid_return	i;
	i = hid_init();
	if (i != HID_RET_SUCCESS) {
		hid = NULL;
   	}
	hid = hid_new_HIDInterface();
	i = hid_force_open(hid, 0, &matcher, 3);
	if (i != HID_RET_SUCCESS) {
  		hid = NULL;
	}
	return hid;
}
hid_return restore_termo(HIDInterface* hid){
	hid_return	i;
	i = hid_close(hid);
	if (i != HID_RET_SUCCESS) {
   		 fprintf(stderr, "hid_close failed with return code %d\n", i);
   	}
	hid_delete_HIDInterface(&hid);
	i = hid_cleanup();	
	if (i != HID_RET_SUCCESS) {
   		 fprintf(stderr, "hid_cleanup failed with return code %d\n",i);
	}
	return i;

}

hid_return read_device(HIDInterface* hid, char* buf,int size){
	hid_return i;
	i = hid_interrupt_read(hid, EP_HID_IN, buf, size, espera);

	if (i != HID_RET_SUCCESS) {
     		fprintf(stderr, "hid_get_input_report failed with return code %d\n", i);
	}
	return i;	
}

unsigned int pack(unsigned char a, unsigned char b){
        unsigned int packed;
        packed = a;
        packed <<= 8;
        packed |= b;
        return packed;
}
