CC=gcc
INCLUDE=include
CFLAGS=-fPIC -Wall -Wextra -O2 -I${INCLUDE}
LDFLAGS=-shared -lSDL2 -lts -lSDL2_ttf -lSDL2_image
RM=rm -f
RMDIR=rmdir
TARGET_LIB=libTouchCP-$(shell uname -m).so
_dummy := $(shell mkdir -p obj) # Create obj dir

SRC_DIR=src
OBJ_DIR=obj
SRCS=$(wildcard $(SRC_DIR)/*.cpp)
OBJS=$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

.PHONY=all
all: ${TARGET_LIB}

$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS}
	-${RMDIR} ${OBJ_DIR}
