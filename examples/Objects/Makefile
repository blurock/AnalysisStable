# FILE     Makefile
# PACKAGE  Objects
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "Objects" package.
#
# COPYRIGHT (C)  1997 Basis Library

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


#I
include ../../etc/Basis/MakeDef

LDLIBS+=\
  -lObjects


#V
ALL=otest

OBJECTS = main.o

LIBS = 	\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
        -lString\
        -lObjects\
        -lCommBuffer\
        -lSystem\
        -lm


#F Targets.

all: $(ALL)

otest: $(OBJECTS)
	CompileC++ -o otest $(OBJECTS) $(LIBS)


cleaner::
	$(RM) $(ALL)

