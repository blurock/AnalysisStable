# FILE     Makefile
# PACKAGE  Integer
# AUTHOR   Wolfgang Stoecher, Andreas Neubacher
#
# CONTENT
#   Makefile for tool "CodeParser".
#
# COPYRIGHT (C)  STURM Project, 1995 RISC Linz

#V
CFLAGS	= -O -Wall
LDLIBS  = -lfl

LEX	= lex
CC      = gcc
ALL     = sturm2texi package2texi

#F Targets.

all:	$(ALL)

sturm2texi.l: sturm2texirules.l sturm2teximain.l sturm2texidef.c \
	      textrules.l textdef.c scdef.c
	cat sturm2texirules.l textrules.l sturm2teximain.l >sturm2texi.l

package2texi.l: package2texirules.l package2teximain.l package2texidef.c \
	      textrules.l textdef.c scdef.c
	cat package2texirules.l textrules.l package2teximain.l >package2texi.l

clean::
	$(RM) *.o *~ sturm2texi package2texi sturm2texi.l package2texi.l

cleaner::  clean
	$(RM) $(ALL)



