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

AULA01 = aula0101 aula0102 aula0103 aula0104 aula0105 aula0106
AULA02 = aula0202a aula0202b aula0202c aula0202d
AULA03 = aula0302a aula0302b aula0302c aula0302d

AULA0101OBJS = aula0101.o
AULA0102OBJS = aula0102.o
AULA0103OBJS = aula0103.o
AULA0104OBJS = aula0104.o
AULA0105OBJS = aula0105.o
AULA0106OBJS = aula0106.o

AULA0202AOBJS = aula0201a.o aula0202.o
AULA0202BOBJS = aula0201b.o aula0202.o
AULA0202COBJS = aula0201c.o aula0202.o
AULA0202DOBJS = aula0201d.o aula0202.o

AULA0302AOBJS = aula0302.o aula0301a.o
AULA0302BOBJS = aula0302.o aula0301b.o
AULA0302COBJS = aula0302.o aula0301c.o
AULA0302DOBJS = aula0302.o aula0301d.o

LIBMATEMATICARECURSAOOBJS = aula0201a.o aula0301a.o
LIBMATEMATICADOWHILEOBJS = aula0201b.o aula0301b.o
LIBMATEMATICAFOROBJS = aula0201c.o aula0301c.o
LIBMATEMATICAWHILEOBJS = aula0201d.o

EXECS = $(AULA01) $(AULA02) $(AULA03)

LIBS = libmatematica-recursao.a libmatematica-dowhile.a libmatematica-for.a libmatematica-while.a

ALL = $(EXECS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $<

all: $(ALL)

aula01: $(AULA01)

aula0101: $(AULA0101OBJS)
	$(LD) $(LFLAGS) -o $@ $(AULA0101OBJS)
	cp -f $@ $@-$(OS)-$(CC)-$(DIALECT)

aula0102: $(AULA0102OBJS)
	$(LD) $(LFLAGS) -o $@ $(AULA0102OBJS)
	cp -f $@ $@-$(OS)-$(CC)-$(DIALECT)

aula0103: $(AULA0103OBJS)
	$(LD) $(LFLAGS) -o $@ $(AULA0103OBJS)
	cp -f $@ $@-$(OS)-$(CC)-$(DIALECT)

aula0104: $(AULA0104OBJS)
	$(LD) $(LFLAGS) -o $@ $(AULA0104OBJS)
	cp -f $@ $@-$(OS)-$(CC)-$(DIALECT)

aula0105: $(AULA0105OBJS)
	$(LD) $(LFLAGS) -o $@ $(AULA0105OBJS)
	cp -f $@ $@-$(OS)-$(CC)-$(DIALECT)

aula0106: $(AULA0106OBJS)
	$(LD) $(LFLAGS) -o $@ $(AULA0106OBJS)
	cp -f $@ $@-$(OS)-$(CC)-$(DIALECT)

aula02: $(AULA02)

aula0202a: $(AULA0202AOBJS)
	$(LD) $(LFLAGS) -o $@ $(AULA0202AOBJS)
	cp -f $@ $@-$(OS)-$(CC)-$(DIALECT)

aula0202b: $(AULA0202BOBJS)
	$(LD) $(LFLAGS) -o $@ $(AULA0202BOBJS)
	cp -f $@ $@-$(OS)-$(CC)-$(DIALECT)

aula0202c: $(AULA0202COBJS)
	$(LD) $(LFLAGS) -o $@ $(AULA0202COBJS)
	cp -f $@ $@-$(OS)-$(CC)-$(DIALECT)

aula0202d: $(AULA0202DOBJS)
	$(LD) $(LFLAGS) -o $@ $(AULA0202DOBJS)
	cp -f $@ $@-$(OS)-$(CC)-$(DIALECT)

aula03: $(AULA03)

aula0302a: $(AULA0302AOBJS)
	$(LD) $(LFLAGS) -o $@ $(AULA0302AOBJS)
	cp -f $@ $@-$(OS)-$(CC)-$(DIALECT)

aula0302b: $(AULA0302BOBJS)
	$(LD) $(LFLAGS) -o $@ $(AULA0302BOBJS)
	cp -f $@ $@-$(OS)-$(CC)-$(DIALECT)

aula0302c: $(AULA0302COBJS)
	$(LD) $(LFLAGS) -o $@ $(AULA0302COBJS)
	cp -f $@ $@-$(OS)-$(CC)-$(DIALECT)

aula0302d: $(AULA0302DOBJS)
	$(LD) $(LFLAGS) -o $@ $(AULA0302DOBJS)
	cp -f $@ $@-$(OS)-$(CC)-$(DIALECT)

libmatematica-recursao.a: $(LIBMATEMATICARECURSAOOBJS)
	ar -r -c $@ $(LIBMATEMATICARECURSAOOBJS)

libmatematica-dowhile.a: $(LIBMATEMATICADOWHILEOBJS)
	ar -r -c $@ $(LIBMATEMATICADOWHILEOBJS)

libmatematica-for.a: $(LIBMATEMATICAFOROBJS)
	ar -r -c $@ $(LIBMATEMATICAFOROBJS)

libmatematica-while.a: $(LIBMATEMATICAWHILEOBJS)
	ar -r -c $@ $(LIBMATEMATICAWHILEOBJS)

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