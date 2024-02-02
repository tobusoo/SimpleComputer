export BIN_DIR = $(PWD)/bin
export OBJ_DIR = $(PWD)/obj

export CFLAGS = -Wall -Werror -I include
export DEPSFLAGS = -MMD
export CC = gcc

SUBDIRS = console myBigChars myReadKey mySimpleComputer myTerm simpleassembler simplebasic

.PHONY: all clean subdirs

all: create_dirs subdirs

create_dirs:
	@mkdir -p $(BIN_DIR) $(OBJ_DIR)

subdirs:
	@$(foreach var,$(SUBDIRS), $(MAKE) --no-print-directory -C $(var);)

clean:
	@rm -rf $(BIN_DIR) $(OBJ_DIR)
