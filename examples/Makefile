SOURCES    := $(wildcard *.c)
PROGRAMS   := $(patsubst %.c,%,$(SOURCES))

CC	   := gcc
LDFLAGS    := -pthread
INCLUDES   :=
CFLAGS     := -g -O0 -Wall $(INCLUDES) -rdynamic

all: $(PROGRAMS)

.c:
	@echo Building $@:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

clean:
	@echo Cleaning up the mess...
	rm -f $(PROGRAMS) *~

re: clean all

.PHONY: all clean re
