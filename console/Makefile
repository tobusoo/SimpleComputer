APP_NAME = pr02
APP_PATH = $(APP_NAME)

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

DEPS = $(OBJ:.o=.d)

.PHONY: all clean
all: $(APP_PATH)

-include $(DEPS)

$(APP_PATH): $(OBJ) $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(DEPSFLAGS) -c -o $@ $<	

clean:
	@rm -rf $(OBJ) $(APP_PATH) $(DEPS) $(APP_PATH)