export CFLAGS = -Wall -Werror -I${PWD}/include
export DEPSFLAGS = -MMD
export CC = gcc

SUBDIRS = myBigChars myReadKey mySimpleComputer myTerm simpleassembler simplebasic console
IMPL_LIBS = mySimpleComputer/libmySimpleComputer.a
export LIBS = $(patsubst %, ${PWD}/%, $(IMPL_LIBS)) 

.PHONY: all clean subdirs

all: subdirs

subdirs:
	@$(foreach var,$(SUBDIRS), $(MAKE) --no-print-directory -C $(var);)

clean:
	@$(foreach var,$(SUBDIRS), $(MAKE) --no-print-directory clean -C $(var);)
