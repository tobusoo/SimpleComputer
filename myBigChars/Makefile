# The library is not implemented

DIR_NAME = myBigChars

LIB_NAME = lib$(DIR_NAME)
LIB_PATH = $(LIB_NAME).a

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

DEPS = $(OBJ:.o=.d)

.PHONY: all 
# all: $(LIB_PATH)
all: 
	@echo [INFO] $(LIB_NAME) is not implemented

-include $(DEPS)

$(LIB_PATH): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(DEPSFLAGS) -c -o $@ $<	

clean:
	@rm -f $(OBJ) $(LIB_PATH) $(DEPS)