APP_NAME = sbt
APP_PATH = $(APP_NAME)

SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))

DEPS = $(OBJ:.o=.d)

.PHONY: all 
all: $(APP_PATH)

-include $(DEPS)

$(APP_PATH): $(OBJ)
	$(CPP) $(CPPFLAGS) -o $@ $^

%.o: %.c
	$(CPP) $(CPPFLAGS) $(DEPSFLAGS) -c -o $@ $<	

clean:
	@rm -f $(OBJ) $(APP_PATH) $(DEPS)