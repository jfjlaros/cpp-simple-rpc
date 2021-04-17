LIB := libsimpleRPC.a
MODULES := interface serial types utils

CC := g++
AR := ar

EXEC := $(basename $(MAIN))
OBJS := $(addsuffix .o, $(MODULES))

.PHONY: all clean distclean


all: $(LIB)

clean:
	rm -f $(OBJS)

distclean: clean
	rm -f $(LIB)


$(LIB): $(OBJS)
	$(AR) rcs $@ $^

%.o: %.cc %.h
	$(CC) -o $@ -c $<
