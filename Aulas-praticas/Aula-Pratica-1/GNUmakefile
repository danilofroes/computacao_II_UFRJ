################################################################################
#
# Universidade Federal do Rio de Janeiro
# Escola Politecnica
# Departamento de Eletronica e de Computacao
# EEL270 - Computacao II - Turma 2025/2
# Prof. Marcelo Luiz Drumond Lanza
# Autor: Danilo Davi Gomes Fróes
#
# Descricao:
#   Arquivo de dependencias especifico para os sistemas operacionais da familia Linux.
#
# $Author$
# $Date$
# $Log$
#
###############################################################################

OS = $(shell uname -s)

CC = gcc

ifeq ($(cc), CLANG)
CC = clang
endif

LD = $(CC)

DIALECT = ansi
STANDARD = -ansi

ifeq ($(dialeto), C89)
DIALECT = c89
STANDARD = -std=c89
endif

ifeq ($(dialeto), C90)
DIALECT = c90
STANDARD = -std=c90
endif

ifeq ($(dialeto), C99)
DIALECT = c99
STANDARD = -std=c99
endif

ifeq ($(dialeto), C11)
DIALECT = c11
STANDARD = -std=c11
endif

DEBUG =

CFLAGS = -Wall $(STANDARD)
LFLAGS = -Wall

AULA01 = aula0101

AULA0101OBJS = aula0101.o

EXECS = $(AULA01)

LIBS =

ALL = $(EXECS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $<

all: $(ALL)

aula01: $(AULA0101OBJS)
	$(LD) $(LFLAGS) -o $@ $(AULA0101OBJS)

aula0101: aula01
	cp -f $@ $@-$(OS)-$(CC)-$(DIALECT)

.PHONY: clean-all clean clean-objs clean-bsd clean-linux clean-gcc clean-clang clean-ansi clean-c89 clean-c90 clean-c99 clean-c11

clean-all:
	rm -f *.o $(ALL) *-FreeBSD-* *-Linux-* *.core

clean:
	rm -f *.o $(ALL) *.core

clean-objs:
	rm -f *.o *.core

clean-bsd:
	rm -f *.o $(ALL) *-FreeBSD-* *.core

clean-linux:
	rm -f *.o $(ALL) *-Linux-* *.core

clean-gcc:
	rm -f *.o $(ALL) *-gcc-* *.core

clean-clang:
	rm -f *.o $(ALL) *-clang-* *.core

clean-ansi:
	rm -f *.o $(ALL) *-ansi-* *.core

clean-c89:
	rm -f *.o $(ALL) *-c89-* *.core

clean-c90:
	rm -f *.o $(ALL) *-c90-* *.core

clean-c99:
	rm -f *.o $(ALL) *-c99-* *.core

clean-c11:
	rm -f *.o $(ALL) *-c11-* *.core

# $RCSfile$