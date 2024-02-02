# The application is not implemented

DIR_NAME = simplebasic

APP_NAME = $(DIR_NAME).a
APP_PATH = $(APP_NAME)

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

DEPS = $(OBJ:.o=.d)

.PHONY: all 
# all: $(APP_PATH)
all: 
	@echo [INFO] $(DIR_NAME) is not implemented

-include $(DEPS)

$(APP_PATH): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(DEPSFLAGS) -c -o $@ $<	

clean:
	@rm -f $(OBJ) $(APP_PATH) $(DEPS)