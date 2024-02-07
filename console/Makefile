APP_NAME = test
APP_PATH = $(APP_NAME)

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

DEPS = $(OBJ:.o=.d)

.PHONY: all clean
all: $(APP_PATH)

-include $(DEPS)

$(APP_PATH): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(DEPSFLAGS) -c -o $@ $<	

clean:
	@rm -rf $(OBJ) $(APP_PATH) $(DEPS)