# FILE     Makefile
# PACKAGE  DataObjects
# AUTHOR   Edward S. Blurock
#
# CONTENT
#   Makefile for example programs of the "DataObjects" package.
#
# COPYRIGHT (C)  1997 CoreObjects Library

#V PackageRoot . . . . . . . . . . . . . . The root directory of this package.
PackageRoot:=$(shell cd ../..; pwd)


#I
include ../../etc/CoreObjects/MakeDef

OBJECTS = main.o 

ALL=otest

LIBS=\
	-L$(PackageRoot)/lib\
	-L$(CodeBaseRoot)/lib\
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

#V

#F Targets.

all: $(ALL)

otest: $(OBJECTS)
	CompileC++ -o otest $(OBJECTS) $(LIBS)

cleaner::
	$(RM) $(ALL)
