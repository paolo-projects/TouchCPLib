CC=g++
INCLUDE=
CFLAGS=-fPIC -Wall -Wextra -O2 ${INCLUDE}
LDFLAGS=-lTouchCPLib
RM=rm -f
TARGET=example

SRCS=onebutton.cpp

.PHONY=all
all: ${TARGET}

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^ ${LDFLAGS} 

.PHONY: clean
clean:
	-${RM} ${TARGET}
