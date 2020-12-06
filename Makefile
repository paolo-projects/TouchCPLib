CC=gcc
INCLUDE=include
CFLAGS=-fPIC -Wall -Wextra -O2 -g -I${INCLUDE}
LDFLAGS=-shared -lSDL2 -lts -lSDL2_ttf -lSDL2_image
RM=rm -f
RMDIR=rmdir
TARGET_LIB=libTouchCP.so

SRC_DIR=src
OBJ_DIR=obj
SRCS=$(wildcard $(SRC_DIR)/*.cpp)
OBJS=$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

.PHONY=all
all: ${TARGET_LIB}

$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -MMD -c -o $@ $<
	
-include $(OBJS:.o=.d)

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.cpp=.d)
	-${RMDIR} ${OBJ_DIR}