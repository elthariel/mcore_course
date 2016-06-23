LIB        := libcommon.a
SOURCES    := $(wildcard *.c)
OBJECTS    := $(patsubst %.c,%.o,$(SOURCES))

CC	   := gcc
LDFLAGS    := -pthread
INCLUDES   :=
CFLAGS     := -g -O0 -Wall $(INCLUDES) -rdynamic

all: $(LIB)

$(LIB): $(OBJECTS)
	ar rcs $(LIB) $<
	ranlib $(LIB)

clean:
	rm -rf $(LIB) $(OBJECTS)
