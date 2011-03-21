Program to use EL-USB-RT USB thermometer under Linux
====================================================

This is a small program to retrieve temperature and humidity from
EL-USB-RT from vendor `Lascar LTD`_.  It is derived from
`Ángel Sancho`_'s `lascar-usb-termometer`_.

This program uses `libhid`_ to communicate with the device.  It can
be downloaded from the `Alioth Debian website`_.


Installing
==========

 * Download `libhid`_ and compile or ``apt-get`` if you use debian-like
   systems. You must also have `libusb-dev` installed.
 * Clone the `github repo`_
 * Compile by running ``make``


Running
=======

Running ``usb_termometer`` will return a single temperature and
humidity reading from the device.  Additional readings can be attained
by tweaking the ``--count`` option.  For example, ``--count=10`` will
return 10 readings and then exit.  Setting ``--count=0`` will collect
data indefinitely.

By default the temperature is returned in Celcius.  Using the
``--farenheit`` flag will return the temperature in Farenheit.

Help can be printed to the screen using the ``--help`` flag::

  Usage: usb_termometer [OPTION...]
  Collect temperature and humidity readings

    -c, --count=count          The number of readings to take; default 1, if 0 go
                             forever
    -d, --debug                Enable debugging
    -f, --farenheit            Get temperature in farenheit; default celcius
    -?, --help                 Give this help list
        --usage                Give a short usage message


.. _Alioth Debian website: http://alioth.debian.org/
.. _Ángel Sancho: angel.sancho@gmail.com
.. _Lascar LTD: http://www.lascarelectronics.com
.. _github repo: https://github.com/rca/lascar-usb-thermometer
.. _hid_get_input_report(): http://libhid.alioth.debian.org/doc/hid__exchange_8c.html#0dd0724b7b0a00026999863e8530cf14
.. _lascar-usb-termometer: http://code.google.com/p/lascar-usb-termometer/
.. _libhid: http://libhid.alioth.debian.org/
.. _libusb-dev: http://packages.debian.org/search?keywords=libusb-dev
