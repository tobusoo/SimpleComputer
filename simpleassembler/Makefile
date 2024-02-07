# The application is not implemented

DIR_NAME = simpleassembler

APP_NAME = $(DIR_NAME)
APP_PATH = $(APP_NAME)

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

DEPS = $(OBJ:.o=.d)

.PHONY: all 
# all: $(APP_PATH)
all: 
	@echo [INFO] $(APP_NAME) is not implemented

-include $(DEPS)

$(APP_PATH): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(DEPSFLAGS) -c -o $@ $<	

clean:
	@rm -f $(OBJ) $(APP_PATH) $(DEPS)