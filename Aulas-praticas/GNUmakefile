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

CFLAGS = -Wall $(STANDARD) $(DEBUG)
LFLAGS = -Wall

AULA0101 = aula0101
AULA0102 = aula0102
AULA0103 = aula0103
AULA0104 = aula0104
AULA0105 = aula0105
AULA0106 = aula0106

AULA0101OBJS = aula0101.o
AULA0102OBJS = aula0102.o
AULA0103OBJS = aula0103.o
AULA0104OBJS = aula0104.o
AULA0105OBJS = aula0105.o
AULA0106OBJS = aula0106.o

EXECS = $(AULA0101) $(AULA0102) $(AULA0103) $(AULA0104) $(AULA0105) $(AULA0106)

LIBS =

ALL = $(EXECS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $<

all: $(ALL)

aula0101: $(AULA0101OBJS)
	$(LD) $(LFLAGS) -o $(AULA0101) $(AULA0101OBJS)
	cp -f $(AULA0101) $(AULA0101)-$(OS)-$(CC)-$(DIALECT)

aula0102: $(AULA0102OBJS)
	$(LD) $(LFLAGS) -o $(AULA0102) $(AULA0102OBJS)
	cp -f $(AULA0102) $(AULA0102)-$(OS)-$(CC)-$(DIALECT)

aula0103: $(AULA0103OBJS)
	$(LD) $(LFLAGS) -o $(AULA0103) $(AULA0103OBJS)
	cp -f $(AULA0103) $(AULA0103)-$(OS)-$(CC)-$(DIALECT)

aula0104: $(AULA0104OBJS)
	$(LD) $(LFLAGS) -o $(AULA0104) $(AULA0104OBJS)
	cp -f $(AULA0104) $(AULA0104)-$(OS)-$(CC)-$(DIALECT)

aula0105: $(AULA0105OBJS)
	$(LD) $(LFLAGS) -o $(AULA0105) $(AULA0105OBJS)
	cp -f $(AULA0105) $(AULA0105)-$(OS)-$(CC)-$(DIALECT)

aula0106: $(AULA0106OBJS)
	$(LD) $(LFLAGS) -o $(AULA0106) $(AULA0106OBJS)
	cp -f $(AULA0106) $(AULA0106)-$(OS)-$(CC)-$(DIALECT)

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