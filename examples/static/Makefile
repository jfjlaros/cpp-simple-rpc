MAIN := demo.cc
LIB := simpleRPC
IPATH := ../../src
LPATH := ../../src
BPATH := ../../src

DEVICE := /dev/ttyACM0
BAUDRATE := 9600
WAIT := 2

CC := g++

EXEC := $(basename $(MAIN))
HEADER := device.h

.PHONY: all distclean headclean header


all: $(EXEC)

distclean: headclean
	rm -f $(EXEC)

headclean:
	rm -f $(HEADER)

header: headclean


$(EXEC): $(MAIN) $(HEADER)
	$(CC) -o $@ $< -I$(IPATH) -L$(LPATH) -l$(LIB)

$(HEADER) header:
	$(BPATH)/generate $(DEVICE) $(BAUDRATE) $(WAIT) > $(HEADER)
