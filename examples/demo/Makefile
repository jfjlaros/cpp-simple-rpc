MAIN := demo.cc
LIB := simpleRPC
IPATH := ../../src
LPATH := ../../src
BPATH := ../../src

CC := g++

EXEC := $(basename $(MAIN))

.PHONY: all distclean


all: $(EXEC)

distclean:
	rm -f $(EXEC)


$(EXEC): $(MAIN) device.h
	$(CC) -o $@ $< -I$(IPATH) -L$(LPATH) -l$(LIB)

device.h:
	$(BPATH)/generate > $@
