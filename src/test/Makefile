OS_TYPE := $(shell sh -c 'uname -s')
COMO_OBJECT_LIB=-lcomoobject
COMO_OBJECT_LIB_LD_FLAGS= -shared
BINDIR = $(shell pwd)/../../bin
CFLAGS = -Wall -Wextra -g -ggdb -std=c99 -I../ -L$(BINDIR) -Wl,-rpath=$(BINDIR)
LIBS := $(COMO_OBJECT_LIB)
SOURCES = $(shell echo *.c)
COMO_OBJECT_LIB_OBJECTS =$(SOURCES:.c=)

all: $(COMO_OBJECT_LIB_OBJECTS)

.c:
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

clean:
	rm -rf $(COMO_OBJECT_LIB_OBJECTS)
