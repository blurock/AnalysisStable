# FILE     Makefile
# PACKAGE  DirectedTreeObjects
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "DirectedTreeObjects" package.
#
# COPYRIGHT (C)  1997 CoreObjects Library

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


#I
include ../../etc/CoreObjects/MakeDef

LDLIBS+=\
  -lDirectedTreeObjects


#V
ALL=otest
OBJECTS=main.o
LIBS=\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
	-lDirectedTreeObjects\
	-lMenuObjects\
	-lInstanceObjects\
	-lOperationObjects\
	-lFunctionReal1DObjects\
	-lLogicalObjects\
	-lNumericObjects\
	-lDataObjects\
	-lCoreDataObjects\
	-lGraph\
	-lMatrixNumeric\
	-lVector\
        -lSystem\
        -lONames\
        -lMixedClasses\
	-lPairs\
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
