PROGRAM = usb_termometer
PROGRAM_FILES = usb_termometer.c

CC = gcc

CFLAGS	+= -g $(shell pkg-config --cflags libhid)
LDFLAGS	+= -g
LIBS 	+= $(shell pkg-config --libs libhid)

SOURCES = $(wildcard *.c)

OBJS = $(SOURCES:.c=.o)

ALL: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM) $(LIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY clean:
	@rm -rf $(PROGRAM)
	@rm -rf $(OBJS)

