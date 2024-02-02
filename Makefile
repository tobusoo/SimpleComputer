export CFLAGS = -Wall -Werror -I include
export DEPSFLAGS = -MMD
export CC = gcc

SUBDIRS = console myBigChars myReadKey mySimpleComputer myTerm simpleassembler simplebasic

.PHONY: all clean subdirs

all: subdirs

subdirs:
	@$(foreach var,$(SUBDIRS), $(MAKE) --no-print-directory -C $(var);)

clean:
	@$(foreach var,$(SUBDIRS), $(MAKE) --no-print-directory clean -C $(var);)
