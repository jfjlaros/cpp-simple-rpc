MAIN := generate.cc
LIB := libsimpleRPC.a
MODULES := serial types utils

CC := g++
AR := ar

EXEC := $(basename $(MAIN))
OBJS := $(addsuffix .o, $(MODULES))

.PHONY: all clean distclean


all: $(EXEC)

clean:
	rm -f $(OBJS)

distclean: clean
	rm -f $(EXEC) $(LIB)


$(EXEC): $(MAIN) $(LIB)
	$(CC) -o $@ $^

$(LIB): $(OBJS)
	$(AR) rcs $@ $^

%.o: %.cc %.h
	$(CC) -o $@ -c $<
