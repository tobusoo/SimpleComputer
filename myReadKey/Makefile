DIR_NAME = myReadKey

LIB_NAME = lib$(DIR_NAME)
LIB_PATH = $(LIB_NAME).a

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

DEPS = $(OBJ:.o=.d)

.PHONY: all 
all: $(LIB_PATH)

-include $(DEPS)

$(LIB_PATH): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(DEPSFLAGS) -c -o $@ $<	

clean:
	@rm -f $(OBJ) $(LIB_PATH) $(DEPS)