APP_NAME = sat
APP_PATH = $(APP_NAME)

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

DEPS = $(OBJ:.o=.d)

.PHONY: all 
all: $(APP_PATH)

-include $(DEPS)

$(APP_PATH): $(OBJ)
	$(CC) $(CFLAGS) -g -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(DEPSFLAGS) -c -o $@ $<	

clean:
	@rm -f $(OBJ) $(APP_PATH) $(DEPS)