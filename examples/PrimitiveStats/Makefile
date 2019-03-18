# FILE     Makefile
# PACKAGE  PrimitiveStats
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "PrimitiveStats" package.
#
# COPYRIGHT (C)  1997 Basis Library

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


#I
include ../../etc/Basis/MakeDef

LDLIBS+=\
  -lPrimitiveStats


#V
ALL=otest

OBJECTS = main.o

LIBS = 	\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
        -lPrimitiveStats\
	-lVector\
        -lSystem\
        -lMixedClasses\
        -lString\
        -lObjects\
        -lCommBuffer\
        -lm
#F Targets.

all: $(ALL)

otest: $(OBJECTS)
	CompileC++ -o otest $(OBJECTS) $(LIBS)



cleaner::
	$(RM) $(ALL)

