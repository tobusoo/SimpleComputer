# The library is not implemented

DIR_NAME = mySimpleComputer

LIB_NAME = $(DIR_NAME).a
LIB_PATH = $(LIB_NAME)

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

DEPS = $(OBJ:.o=.d)

.PHONY: all 
# all: $(LIB_PATH)
all: 
	@echo [INFO] $(DIR_NAME) is not implemented

-include $(DEPS)

$(LIB_PATH): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(DEPSFLAGS) -c -o $@ $<	

clean:
	@rm -f $(OBJ) $(LIB_PATH) $(DEPS)