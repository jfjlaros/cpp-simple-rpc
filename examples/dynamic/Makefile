MAIN := demo.cc
LIB := simpleRPC
IPATH := ../../src
LPATH := ../../src

CC := g++

EXEC := $(basename $(MAIN))

.PHONY: all distclean


all: $(EXEC)

distclean:
	rm -f $(EXEC)


$(EXEC): $(MAIN)
	$(CC) -o $@ $< -I$(IPATH) -L$(LPATH) -l$(LIB)
