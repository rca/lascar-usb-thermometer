PROGRAM = usb_termometer
PROGRAM_FILES = usb_termometer.c

CC = gcc

CFLAGS	+= -g $(shell pkg-config --cflags libhid)
LDFLAGS	+= -g
LIBS 	+= $(shell pkg-config --libs libhid) 

ALL: $(PROGRAM_FILES)
	$(CC) $(PROGRAM_FILES) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM) $(LIBS)

clean:
	@rm -rf $(PROGRAM)

