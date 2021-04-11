MAIN := test


CC := g++


.PHONY: all distclean


all: $(MAIN)

$(MAIN): $(MAIN).cc device.h
	$(CC) -o $@ $<

distclean:
	rm -f $(MAIN)
