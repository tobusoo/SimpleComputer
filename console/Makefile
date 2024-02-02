APP_NAME = test
APP_PATH = $(BIN_DIR)/$(APP_NAME)

DIR_NAME = console
DIR_OBJ_PATH = $(OBJ_DIR)/$(DIR_NAME)

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, $(DIR_OBJ_PATH)/%.o, $(SRC))

DEPS = $(OBJ:.o=.d)

.PHONY: all obj_dir
all: obj_dir $(APP_PATH)
-include $(DEPS)

obj_dir:
	@mkdir -p $(DIR_OBJ_PATH)

$(APP_PATH): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(DIR_OBJ_PATH)/%.o: %.c
	$(CC) $(CFLAGS) $(DEPSFLAGS) -c -o $@ $<	
