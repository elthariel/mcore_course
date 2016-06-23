SOURCES    := $(wildcard *.c)
PROGRAMS   := $(patsubst %.c,%,$(SOURCES))

CC	   := gcc
LDFLAGS    := -pthread ../lib/libcommon.a
INCLUDES   := -I../lib
CFLAGS     := -g -O0 -Wall $(INCLUDES) -rdynamic

all: $(PROGRAMS)

.c:
	@echo Building $@:
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	@echo Cleaning up the mess...
	rm -f $(PROGRAMS) *~

re: clean all

.PHONY: all clean re
