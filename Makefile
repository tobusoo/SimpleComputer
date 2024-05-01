export CFLAGS = -Wall -Werror -I${PWD}/include
export CPPFLAGS = CFLAGS
export DEPSFLAGS = -MMD
export CC = gcc
export CPP = g++

SUBDIRS = myBigChars myReadKey mySimpleComputer myTerm simpleassembler simplebasic console
IMPL_LIBS = mySimpleComputer/libmySimpleComputer.a myTerm/libmyTerm.a myBigChars/libmyBigChars.a myReadKey/libmyReadKey.a
export LIBS = $(patsubst %, ${PWD}/%, $(IMPL_LIBS)) 

.PHONY: all clean subdirs

all: subdirs

subdirs:
	@$(foreach var,$(SUBDIRS), $(MAKE) --no-print-directory -C $(var);)

clean:
	@$(foreach var,$(SUBDIRS), $(MAKE) --no-print-directory clean -C $(var);)
