CC=g++
CFLAGS=-Wall -Wextra -w -g -O3 --std=c++11
LDFLAGS=
SRCFILES=$(wildcard *.cc)
OBJFILES=$(SRCFILES:.cc=.o)
DEPFILES=$(SRCFILES:.cc=.d)
TARGET=oset
.PHONY: all clean

all: $(TARGET)

-include $(DEPFILES)

oset: $(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) -o oset $(LDFLAGS)

%.o: %.cc Makefile
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

clean:
	-@rm -f $(TARGET) $(OBJFILES) $(DEPFILES)

print-%: ; @echo $*=$($*)