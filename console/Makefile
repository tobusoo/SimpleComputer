APP_NAME = pr05
APP_PATH = $(APP_NAME)

APP_FONT = font

ALL_SRC = $(wildcard *.c)
SRC = $(subst font.c,,$(ALL_SRC))
OBJ = $(patsubst %.c, %.o, $(SRC))

DEPS = $(OBJ:.o=.d)

.PHONY: all clean
all: $(APP_PATH) $(APP_FONT)

-include $(DEPS)

$(APP_FONT): font.o $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^

$(APP_PATH): $(OBJ) $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(DEPSFLAGS) -c -o $@ $<	

clean:
	@rm -rf $(OBJ) $(APP_PATH) $(DEPS) $(APP_PATH) *.[aod] $(APP_FONT)