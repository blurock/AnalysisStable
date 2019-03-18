# FILE     Makefile
# PACKAGE  NumericObjects
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "NumericObjects" package.
#
# COPYRIGHT (C)  1997 CoreObjects Library

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


#I
include ../../etc/CoreObjects/MakeDef

ALL=otest 

OBJECTS = main.o 

LIBS=\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
	-lNumericObjects\
	-lCoreDataObjects\
        -lSystem\
	-lPairs\
        -lONames\
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
