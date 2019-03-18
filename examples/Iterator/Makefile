# FILE     Makefile
# PACKAGE  Iterator
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "Iterator" package.
#
# COPYRIGHT (C)  1997 CoreObjects Library

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


#I
include ../../etc/CoreObjects/MakeDef

LDLIBS+=\
  -lIterator


#V
ALL=otest
OBJECTS=main.o
LIBS=\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
        -lIterator\
	-lInstanceObjects\
	-lDataObjects\
	-lOperationObjects\
	-lLogicalOperations\
	-lNumericOperations\
	-lFunctionReal1DObjects\
	-lParameterizedFunction\
	-lLogicalObjects\
	-lNumericObjects\
	-lCoreDataObjects\
	-lNonStandard\
        -lSystem\
        -lCommBuffer\
        -lONames\
        -lMixedClasses\
	-lMatrixNumeric\
        -lGraph\
	-lPairs\
	-lVector\
        -lString\
        -lObjects\
        -lm

#F Targets.

all: $(ALL)

otest: $(OBJECTS)
	CompileC++ -o otest $(OBJECTS) $(LIBS)

run: 
	otest Initial test 0 < program.prg

cleaner::
	$(RM) $(ALL)
