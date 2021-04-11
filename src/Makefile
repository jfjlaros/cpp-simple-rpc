MAIN := test


CC := g++


OBJS := serial.o

.PHONY: all distclean


all: $(MAIN)

distclean:
	rm -f $(MAIN)


generate: generate.cc $(OBJS)
	$(CC) -o $@ $< $(OBJS)

$(MAIN): $(MAIN).cc $(OBJS)
	$(CC) -o $@ $< $(OBJS)

%.o: %.cc %.h
	$(CC) -o $@ -c $<

device.h: generate
	./generate
