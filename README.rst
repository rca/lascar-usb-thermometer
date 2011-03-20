Program to use EL-USB-RT USB thermometer under Linux
====================================================

This is a small program to retrieve temperature and humidity from
EL-USB-RT from vendor lascar ltd (http://www.lascarelectronics.com).
It is derived from `Ángel Sancho`_'s lascar-usb-termometer, which can
be found at:

.. _Ángel Sancho: angel.sancho@gmail.com

http://code.google.com/p/lascar-usb-termometer/

In order to compile this program you must to have in your system "libhid"
installed.

You can download source code and compile it from:

http://libhid.alioth.debian.org/


Known Bugs
==========

Sometimes shown value (in temp or hum.) doesn't make sense. I don't know why
it happens. I am actually testing another way to access the thermometer, for
example, sending control commands to usb device via hid_get_input_report.


Installing
==========

 * Download libhid from http://libhid.alioth.debian.org/ and compile or apt-get if you use debian like systems. You must also have installed libusb-devel.

 * Clone the git repo at https://github.com/rca/lascar-usb-thermometer

 * Compile by running `make`

Running
=======

Running `usb_termometer` will return a single temperature and humidity
reading from the device.  Additional readings can be attained by
tweaking the `--count` option.  For example, `--count=10` will return
10 readings and then exit.  Setting count to 0 will collect data
indefinitely.

By default the temperature is returned in Celcius.  Using the
`--farenheit` flag will return the temperature in Farenheit.

Help can be printed to the screen using the `--help` flag::

  Usage: usb_termometer [OPTION...]
  Collect temperature and humidity readings

    -c, --count=count          The number of readings to take; default 1, if 0 go
                             forever
    -d, --debug                Enable debugging
    -f, --farenheit            Get temperature in farenheit; default celcius
    -?, --help                 Give this help list
        --usage                Give a short usage message

