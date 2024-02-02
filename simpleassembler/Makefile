# The application is not implemented

DIR_NAME = simpleassembler
DIR_OBJ_PATH = $(OBJ_DIR)/$(DIR_NAME)

LIB_NAME = $(DIR_NAME).a
LIB_PATH = $(BIN_DIR)/$(LIB_NAME)

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, $(DIR_OBJ_PATH)/%.o, $(SRC))

DEPS = $(OBJ:.o=.d)

.PHONY: all obj_dir 
# all: obj_dir $(LIB_PATH)
all: obj_dir # The application is not implemented
-include $(DEPS)

obj_dir:
	@mkdir -p $(DIR_OBJ_PATH)

$(LIB_PATH): $(OBJ)
	ar rcs $@ $^

$(DIR_OBJ_PATH)/%.o: %.c
	$(CC) $(CFLAGS) $(DEPSFLAGS) -c -o $@ $<	
