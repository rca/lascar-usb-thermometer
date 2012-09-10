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

#include <argp.h>
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

/**
 * using argp to parse arguments
 * http://www.gnu.org/s/libc/manual/html_node/Argp-Example-3.htlm
 */
/* Program documentation. */
static char doc[] =
  "Collect temperature and humidity readings";

/* A description of the arguments we accept. */
static char args_doc[] = "";

struct arguments {
  int count, debug, farenheit;
};

/* parse a single option. */
static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  struct arguments *arguments = state->input;

  switch (key) {
  case 'n':
    arguments->count = atoi(arg);
    break;
  case 'd':
    arguments->debug = 1;
    break;
  case 'f':
    arguments->farenheit = 1;
    break;
  default:
    return ARGP_ERR_UNKNOWN;
  }

  return 0;
}

static struct argp_option options[] = {
  {"num", 'n', "num", 0,
   "The number of readings to take; default 1, if 0 go forever"},
  {"debug", 'd', 0, 0, "Enable debugging" },
  {"farenheit", 'f', 0, 0, "Get temperature in farenheit; default celcius" },
  { 0 }
};

static struct argp argp = { options, parse_opt, args_doc, doc };

int main(int argc, char *argv[])
{
    char packet[] = {0x00, 0x00, 0x00};
    HIDInterface* hid = NULL;
    hid_return ret;

    float temp, hum;
    float last_temp, last_hum;

    int status = 0;
    int error_count = 0;

    int *arg_index = NULL;

    int count = 0;

    struct arguments arguments;

    /* default argument values. */
    arguments.count = 1; /* infinite */
    arguments.debug = 0;
    arguments.farenheit = 0;

    if(argp_parse(&argp, argc, argv, 0, 0, &arguments) != 0) {
      exit(-1);
    }

    /* setup debugging to stderr if requested */
    if(arguments.debug) {
        hid_set_debug(HID_DEBUG_ALL);
        hid_set_debug_stream(stderr);
    }

    if((hid=init_termo(hid)) == NULL) {
        fprintf(stderr, "Device NOT present.\n");
        exit(-1);
    }

    while(1) {
        status = 0;

        ret = get_reading(hid, packet, &temp, &hum, arguments.farenheit);
        if(ret != HID_RET_SUCCESS) {
            status = -1;
        }

        if(status == 0) {
            if(temp != last_temp || hum != last_hum) {
                printf("temp: %.1f, hum: %.1f\n", temp, hum);
                fflush(stdout);

                last_temp = temp;
                last_hum = hum;
                count ++;
              }

            /* reset the error count on successful read */
            error_count = 0;
        } else if(error_count > MAX_ERRORS) {
            fprintf(stderr, "Too many errors to continue\n");
            exit(-1);
        } else {
            error_count++;
        }

        if(arguments.count && count >= arguments.count) {
            break;
        } else {
            sleep(SLEEP_TIME);
        }
    }

    restore_termo(hid);

    return 0;
}
