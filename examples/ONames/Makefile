# FILE     Makefile
# PACKAGE  ONames
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "ONames" package.
#
# COPYRIGHT (C)  1997 Basis Library

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


#I
include ../../etc/Basis/MakeDef

LIBS =\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
	-lONames\
        -lMixedClasses\
        -lSystem\
        -lCommBuffer\
        -lObjects\
        -lMixedClasses\
        -lString\
        -lm

OBJECTS= main.o

#V
ALL=otest

otest: $(OBJECTS)
	CompileC++ -o otest $(OBJECTS) $(LIBS)

#F Targets.

all: $(ALL)


cleaner::
	$(RM) $(ALL)
